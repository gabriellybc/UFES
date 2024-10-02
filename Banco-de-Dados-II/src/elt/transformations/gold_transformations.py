from src.utils.db_utils import DuckDBConnection


class GoldTransformer:
    def __init__(self, db_connection: 'DuckDBConnection', config: dict) -> None:
        self.db_connection = db_connection
        self.config = config
    

    def create_tables(self) -> None:
        """Cria as tabelas necessárias no esquema gold."""
        self.db_connection.execute("""
            CREATE SCHEMA IF NOT EXISTS gold;
        """)

        self.db_connection.execute("""
            CREATE TABLE IF NOT EXISTS gold.dim_tempo AS
            SELECT
                id,
                data,
                EXTRACT(YEAR FROM data) AS ano,
                EXTRACT(MONTH FROM data) AS mes,
                EXTRACT(DAY FROM data) AS dia,
                EXTRACT(WEEK FROM data) AS semana,
                EXTRACT(QUARTER FROM data) AS trimestre,
                IF(EXTRACT(MONTH FROM data) <= 6, 1, 2) AS semestre,
                STRFTIME(data, '%Y-%m-%d') AS data_str
            FROM silver.tempo;
        """)

        self.db_connection.execute("""
            CREATE OR REPLACE TABLE gold.dim_acoes (
                id INTEGER PRIMARY KEY,
                ticker VARCHAR,
                name VARCHAR,
                logo VARCHAR,
                sector VARCHAR,
                type VARCHAR,
            );
        """)

        self.db_connection.execute("""
            CREATE OR REPLACE TABLE gold.fact_indicadores (
                id INTEGER PRIMARY KEY,
                tempo_id INTEGER,
                acao_id INTEGER,
                ticker VARCHAR,
                cotacao FLOAT,
                p_vp FLOAT,
                dividend_yield FLOAT,
                ev_ebit FLOAT,
                roic FLOAT,
                p_l FLOAT,
                liquidez_2_meses FLOAT,
                cres_rec_5a FLOAT
            );
        """)

        self.db_connection.execute("""
            CREATE OR REPLACE TABLE gold.fact_oportunidades (
                id INTEGER PRIMARY KEY,
                tempo_id INTEGER,
                acao_id INTEGER,
                ticker VARCHAR,
                cotacao FLOAT,
                p_vp FLOAT,
                dividend_yield FLOAT,
                ev_ebit FLOAT,
                roic FLOAT,
                p_l FLOAT
            );
        """)

        self.db_connection.execute("""
            CREATE OR REPLACE TABLE gold.dim_tipo (
                id INTEGER PRIMARY KEY,
                tipo_ativo VARCHAR,
                tipo_acao VARCHAR,
                tipo_negociacao VARCHAR
            );
        """)

        self.db_connection.execute("""
            CREATE OR REPLACE TABLE gold.dim_usuarios (
                id INTEGER PRIMARY KEY,
                nome VARCHAR,
                email VARCHAR
            );
        """)

        self.db_connection.execute("""
            CREATE OR REPLACE TABLE gold.fact_negociacoes (
                id INTEGER PRIMARY KEY,
                usuario_id INTEGER,
                acao_id INTEGER,
                tempo_id INTEGER,
                tipo_id INTEGER,
                ticker VARCHAR,
                quantidade INTEGER,
                valor_total FLOAT,
                cotacao FLOAT,
                p_vp FLOAT,
                dividend_yield FLOAT,
                ev_ebit FLOAT,
                roic FLOAT,
                p_l FLOAT,
                liquidez_2_meses FLOAT,
                cres_rec_5a FLOAT
            );
        """)


    def transform(self) -> None:
        self.db_connection.execute(f"""
            INSERT INTO gold.dim_tempo
            SELECT
                new.id,
                new.data,
                EXTRACT(YEAR FROM new.data) AS ano,
                EXTRACT(MONTH FROM new.data) AS mes,
                EXTRACT(DAY FROM new.data) AS dia,
                EXTRACT(WEEK FROM new.data) AS semana,
                EXTRACT(QUARTER FROM new.data) AS trimestre,
                IF(EXTRACT(MONTH FROM new.data) <= 6, 1, 2) AS semestre,
                STRFTIME(new.data, '%Y-%m-%d') AS data_str
            FROM silver.tempo AS new
            LEFT JOIN gold.dim_tempo AS old
                ON new.id = old.id
            WHERE old.id IS NULL
        """)

        self.db_connection.execute(f"""
            INSERT INTO gold.dim_acoes
            SELECT
                row_number() OVER (ORDER BY ticker, name, logo, sector, type) AS id,
                ticker,
                name,
                logo,
                sector,
                type
            FROM (
                SELECT DISTINCT
                    ticker,
                    name,
                    logo,
                    sector,
                    type
                FROM silver.brapi_quote_list
            ) AS distinct_brapi_quote_list;
        """)

        self.db_connection.execute(f"""
            INSERT INTO gold.dim_tipo
            SELECT
                row_number() OVER (ORDER BY tipo_ativo, tipo_acao, tipo_negociacao) AS id,
                tipo_ativo,
                tipo_acao,
                tipo_negociacao
            FROM (
                SELECT DISTINCT
                    tipo_ativo,
                    tipo_acao,
                    tipo_negociacao
                FROM silver.negociacoes
            ) AS distinct_negociacoes;
        """)

        self.db_connection.execute(f"""
            INSERT INTO gold.dim_usuarios
            SELECT
                row_number() OVER (ORDER BY nome, email) AS id,
                nome,
                email
            FROM (
                SELECT DISTINCT
                    nome,
                    email
                FROM silver.usuarios
            ) AS distinct_usuarios;
        """)

        self.db_connection.execute(f"""
            INSERT INTO gold.fact_indicadores
            SELECT DISTINCT
                fd.id,
                tempo.id AS tempo_id,
                brapi.id AS acao_id,
                fd.ticker,
                COALESCE(fd.cotacao, brapi.close) AS cotacao,
                fd.p_vp,
                fd.dividend_yield,
                fd.ev_ebit,
                fd.roic,
                fd.p_l,
                fd.liquidez_2_meses,
                fd.cres_rec_5a
            FROM silver.fundamentus_resultado AS fd
            LEFT JOIN silver.tempo AS tempo
                ON fd.extracted_date = tempo.data
            LEFT JOIN silver.brapi_quote_list AS brapi
                ON fd.ticker = brapi.ticker
                AND fd.extracted_date = brapi.extracted_date
        """)

        self.db_connection.execute(f"""
            INSERT INTO gold.fact_oportunidades
            SELECT DISTINCT
                id,
                tempo_id,
                acao_id,
                ticker,
                cotacao,
                p_vp,
                dividend_yield,
                ev_ebit,
                roic,
                p_l
            FROM gold.fact_indicadores
            WHERE 
                liquidez_2_meses > 100000
                AND cotacao > 0
                AND ev_ebit > 0
                AND p_vp < 1
                AND roic > 0.1
                AND p_l > 0
                AND cres_rec_5a > 0
            QUALIFY ROW_NUMBER() OVER (
                PARTITION BY ticker, cotacao, p_vp, dividend_yield, ev_ebit, roic, p_l
                ORDER BY ticker, cotacao, p_vp, dividend_yield, ev_ebit, roic, p_l
            ) = 1
        """)

        self.db_connection.execute(f"""
            INSERT INTO gold.fact_negociacoes
            SELECT DISTINCT
                neg.id,
                neg.usuario_id,
                fi.acao_id,
                tempo.id AS tempo_id,
                tipo.id AS tipo_id,
                neg.ticker,
                IF(neg.tipo_negociacao = 'venda', -neg.quantidade, neg.quantidade) AS quantidade,
                (fi.cotacao * neg.quantidade) AS valor_total,
                fi.cotacao,
                fi.p_vp,
                fi.dividend_yield,
                fi.ev_ebit,
                fi.roic,
                fi.p_l,
                fi.liquidez_2_meses,
                fi.cres_rec_5a
            FROM silver.negociacoes AS neg
            LEFT JOIN silver.tempo AS tempo
                ON neg.data_movimentacao = tempo.data
            LEFT JOIN gold.fact_indicadores AS fi
                ON neg.ticker = fi.ticker
                AND tempo.id = fi.tempo_id
            LEFT JOIN gold.dim_tipo AS tipo
                ON neg.tipo_ativo = tipo.tipo_ativo
                AND neg.tipo_acao = tipo.tipo_acao
                AND neg.tipo_negociacao = tipo.tipo_negociacao
        """)

        print("Dados transformados na camada Gold.")