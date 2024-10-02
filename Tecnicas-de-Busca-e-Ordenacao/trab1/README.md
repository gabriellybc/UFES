# Makefile:
## Uso:
    - 'make' ou 'make all': compila o trabalho
    - 'make run': executa o trabalho (compila caso não esteja compilado)
    - 'make valgrind': roda o trabalho com o valgrind (compila caso não esteja compilado)
    - 'make clean': apaga os arquivos e diretórios gerados
## Variáveis:
    - PROJ_NAME = nome do arquivo compilado e linkado
    - MAIN_FILE = path do arquivo main.c
    - MAIN_PARAM = parametros para passar para a main na hora de executar o arquivo compilado
    - CC_FLAGS = flags do compilador
    - LINK_FLAGS = flags do linker (-lm para incluir math.h)
    - VALGRIND_PARAM = parametros do valgrind (--leak-check=full, etc)
