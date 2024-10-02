import duckdb
from pathlib import Path
import pandas as pd


class DuckDBConnection:
    def __init__(self, db_path: str) -> None:
        """
        Inicializa a conexão com o banco de dados DuckDB.

        :param db_path: Caminho para o arquivo do banco de dados DuckDB.
        """
        self.db_path = Path(db_path)
        self.conn = self.connect()


    def connect(self) -> duckdb.DuckDBPyConnection:
        """Conecta ao banco de dados DuckDB no caminho especificado."""
        return duckdb.connect(str(self.db_path))
    

    def execute(self, query: str) -> None:
        """
        Executa uma query SQL.

        :param query: A consulta SQL a ser executada.
        """
        self.conn.execute(query)


    def sql(self, query: str) -> pd.DataFrame:
        """
        Executa uma query SQL e retorna um DataFrame.

        :param query: A consulta SQL a ser executada.
        :return: Um DataFrame contendo os resultados da consulta.
        """
        return self.conn.sql(query).df()


    def save_parquet(self, table_name: str, output_path: str) -> None:
        """
        Salva uma tabela DuckDB como Parquet.

        :param table_name: Nome da tabela a ser salva.
        :param output_path: Caminho onde o arquivo Parquet será salvo.
        """
        output_path = Path(output_path)
        query = f"COPY (SELECT * FROM {table_name}) TO '{output_path}' (FORMAT 'parquet')"
        self.conn.execute(query)


    def close(self) -> None:
        """Fecha a conexão com o banco de dados."""
        self.conn.close()
