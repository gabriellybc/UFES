# Investments Dashboard

## Descrição
O Investments Dashboard é um pipeline ELT (Extract, Load, Transform) desenvolvido para processar e analisar dados financeiros de várias fontes. O objetivo é organizar e preparar esses dados para análise, utilizando uma arquitetura de camadas (Bronze, Silver e Gold) que segue as melhores práticas de engenharia de dados.

## Estrutura do Projeto

```
investments-dashboard/
├── configs/
│   └── settings.yaml
├── data/
│   ├── bronze/
│   │   ├── brapi/
│   │   │   └── ...
│   │   ├── fundamentus/
│   │   │   └── ...
│   │   └── sheets/
│   │       └── ...
│   ├── gold/
│   │   ├── dim_acoes.parquet
│   │   ├── dim_tempo.parquet
│   │   ├── dim_tipo.parquet
│   │   ├── dim_usuarios.parquet
│   │   ├── fact_indicadores.parquet
│   │   ├── fact_negociacoes.parquet
│   │   └── fact_oportunidades.parquet
│   └── usuarios_negociacoes.xlsx
├── db/
│   └── database.db
├── main.py
├── Makefile
├── requirements.txt
└── src/
    ├── __init__.py
    ├── elt/
    │   ├── __init__.py
    │   ├── extract.py
    │   ├── load.py
    │   ├── transform.py
    │   └── transformations/
    │       ├── __init__.py
    │       ├── bronze_transformations.py
    │       ├── silver_transformations.py
    │       └── gold_transformations.py
    └── utils/
        ├── __init__.py
        └── db_utils.py
```


## Descrição dos Diretórios e Arquivos
- **configs/**: Contém arquivos de configuração, como ``settings.yaml``.
- **data/**: Diretório onde os dados são armazenados em diferentes camadas (Bronze e Gold).
- **db/**: Contém o banco de dados DuckDB.
- **src/**: Diretório contendo o código-fonte do projeto.
  - **elt/**: Scripts de Extração, Transformação e Carga (ETL).
  - **utils/**: Utilitários e funções auxiliares.
- **main.py**: Script principal para executar o pipeline ETL.
- **Makefile**: Arquivo de automação de tarefas.
- **requirements.txt**: Lista de dependências do projeto.

## Configuração
Edite o arquivo **configs/settings.yaml** para ajustar os caminhos e outras configurações conforme necessário:

```
paths:
  bronze: 'data/bronze'
  gold: 'data/gold'
  db: 'db/database.db'
  usuarios_negociacoes: 'data/usuarios_negociacoes.xlsx'
```

## Dados
### Camada Bronze
A camada Bronze contém dados brutos extraídos de várias fontes, armazenados em formato Parquet. As fontes incluem:

- **Fundamentus**: Dados financeiros de ações.
- **Brapi**: Dados de cotações de ações.
- **Sheets**: Dados de negociações de usuários extraídos de uma planilha Excel.

### Camada Silver
A camada Silver contém dados transformados e limpos, prontos para serem carregados na camada Gold. As transformações incluem limpeza de dados, normalização e junção de diferentes fontes.

### Camada Gold
A camada Gold contém dados finais, organizados em tabelas dimensionais e factuais, prontos para análise. Exemplos de tabelas incluem:

- **dim_acoes**: Dimensão de ações.
- **dim_tempo**: Dimensão de tempo.
- **dim_tipo**: Dimensão de tipos em relação a ativos.
- **dim_usuarios**: Dimensão de usuários.
- **fact_indicadores**: Fato de indicadores financeiros.
- **fact_negociacoes**: Fato de negociações.
- **fact_oportunidades**: Fato de oportunidades de investimento.

## Uso
Executando o Pipeline de ETL

Para executar o pipeline de ETL, utilize o comando:

```
make run
```

## Makefile
O Makefile contém comandos úteis para facilitar a execução de tarefas comuns:

- ``make init``: Cria e ativa um ambiente virtual.
- ``make install``: Instala as dependências do projeto.
- ``make run``: Executa o pipeline de ETL.
- ``make clean``: Remove arquivos temporários e de cache.

## Dependências
Aqui estão as dependências do projeto listadas no arquivo ``requirements.txt``:

```
pandas==2.2.3
duckdb==1.1.0
requests==2.32.3
pyyaml==6.0.2
lxml==5.3.0
pyarrow==17.0.0
fastparquet==2024.5.0
openpyxl==3.1.5
yfinance==0.2.43
```
