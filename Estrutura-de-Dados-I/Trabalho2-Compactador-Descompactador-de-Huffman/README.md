# Compactador/Descompactador de Huffman

Implementação de forma simplificada um programa compactador e descompactador de arquivos. Nele, o usuário poderia inserir um arquivo, de forma a gerar um novo arquivo compactado, com base na codificação de Huffman. A codificação, visa reduzir o espaço ocupado por cada caractere, de forma a estabelecer a própria codificação com os caracteres utilizados com maior frequência, ocupando respetivamente os valores de menos espaço no arquivo. De forma análoga, o
programa também seria capaz de restaurar o arquivo original, a partir de um arquivo compactado pelo mesmo.

Para isso, foi utilizado principalmente TADs para organizar as informações de Arquivos, Codificações, e Bitmap. Além de que alguns desses TADs eram organizados em Listas Duplamente Encadeadas com Sentinela, que também são TADs, uma para cada tipo diferente, tudo utilizando a linguagem de programação C.

# Makefile

Para compilar: "make all", serão gerados os arquivo 'Compacta' e 'Descompacta'.

Para limpar: "make clear", os arquivos objetos serão apagados.

             "make rmproper", os executáveis 'Compacta' e 'Descompacta' serão apagados junto com os arquivos objetos.

# Guia de Execução

Os arquivos principais do trabalho são compactador.c e descompactador.c. Os scripts devem ser chamado de dentro da pasta Codigo, ou seja, o "make all" deve ser executado dentro da pasta Codigo. A partir disso, os executáveis devem ser chamados passando os arquivos que serão compactados e descompactados.

Por exemplo, para compactar o arquivo 'arq.txt', depois do "make all", o Compacta será chamado passando o arquivo: './Compacta arq.txt'. Esse irá gerar o arquivo compactado 'arq.txt.comp'.

Para descompactar o arquivo com extensão '.comp', o Descompactador deverá ser chamado passando o arquivo compactado: './Descompacta arq.txt.comp'. Ele irá gerar o arquivo descompactado com o nome 'arq.txt'.
