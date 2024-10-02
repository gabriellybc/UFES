import gc
import requests
import pandas as pd
from pathlib import Path
from datetime import datetime
from io import StringIO
# import yfinance as yf
pd.set_option('display.max_columns', None)

class DataExtractor:
    def __init__(self, config: dict) -> None:
        """
        Inicializa o extrator de dados.

        :param config: Dicionário de configuração contendo caminhos e outras informações.
        """
        self.config = config

    def extract_fundamentus(self) -> None:
        """Extrai dados de ações do site Fundamentus e os salva em Parquet."""
        url = 'http://www.fundamentus.com.br/resultado.php'
        headers = {
            "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36"
        }
        response = requests.get(url, headers=headers)
        response.raise_for_status()
        df_tabelas = pd.read_html(StringIO(response.text), decimal=',', thousands='.')
        df_tabela_acoes = df_tabelas[0]
        df_tabela_acoes.columns = df_tabela_acoes.columns.str.lower().str.replace(' ', '_').str.replace('/', '_').str.replace('.', '')
        df_tabela_acoes["_extracted_date"] = pd.Timestamp.now().normalize()
        formatted_datetime = datetime.now().strftime("%Y-%m-%d")
        bronze_path = Path(self.config['paths']['bronze']) / 'fundamentus' / f'{formatted_datetime}.parquet'
        df_tabela_acoes.to_parquet(bronze_path, index=False)
        print(f"Dados extraídos e salvos em {bronze_path}")
    

    def extract_brapi(self) -> None:
        """Extrai dados de ações da API brapi e os salva em Parquet."""
        url = 'https://brapi.dev/api/quote/list'
        response = requests.get(url)
        response.raise_for_status()
        tickers = response.json()['stocks']
        list_info_acoes = []
        for ticker in tickers:
            dict_info_acoes = {
                'stock': ticker.get('stock'),
                'name': ticker.get('name'),
                'close': ticker.get('close'),
                'change': ticker.get('change'),
                'volume': ticker.get('volume'),
                'market_cap': ticker.get('market_cap'),
                'logo': ticker.get('logo'),
                'sector': ticker.get('sector'),
                'type': ticker.get('type'),
            }
            list_info_acoes.append(dict_info_acoes)
        df_info_acoes = pd.DataFrame(list_info_acoes)
        df_info_acoes["_extracted_date"] = pd.Timestamp.now().normalize()
        formatted_datetime = datetime.now().strftime("%Y-%m-%d")
        bronze_path = Path(self.config['paths']['bronze']) / 'brapi' / f'{formatted_datetime}.parquet'
        df_info_acoes.to_parquet(bronze_path, index=False)
        print(f"Dados extraídos e salvos em {bronze_path}")


    def extract_usuarios_negociacoes(self) -> None:
        """Extrai dados da sheets e os salva em Parquet."""
        usuarios_negociacoes_path = Path(self.config['paths']['usuarios_negociacoes'])
        df_usuarios = pd.read_excel(usuarios_negociacoes_path, sheet_name="usuarios")
        df_usuarios["_extracted_date"] = pd.Timestamp.now().normalize()
        bronze_path = Path(self.config['paths']['bronze']) / 'sheets' / 'usuarios' / 'usuarios.parquet'
        df_usuarios.to_parquet(bronze_path, index=False)
        print(f"Dados extraídos e salvos em {bronze_path}")

        for row in df_usuarios.itertuples(index=False):
            df_negociacoes = pd.read_excel(usuarios_negociacoes_path, sheet_name=str(row.id))
            df_negociacoes["usuario_id"] = str(row.id)
            df_negociacoes["_extracted_date"] = pd.Timestamp.now().normalize()
            bronze_path = Path(self.config['paths']['bronze']) / 'sheets' / 'negociacoes' / f'{row.id}.parquet'
            df_negociacoes.to_parquet(bronze_path, index=False)
            del df_negociacoes
            gc.collect()
    print(f"Transações extraídas e salvas")
