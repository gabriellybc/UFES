### MAKEFILE ###

all:
				gcc -c *.c
				gcc bitmap.o arvore.o arquivos.o listaArvore.o codificacao.o listaCodificacao.o compactador.o -o Compacta -lm
				gcc bitmap.o arvore.o arquivos.o descompactador.o -o Descompacta -lm

clean:
				rm -rf ./*.o

rmproper: clean
				rm -rf ./Compacta
				rm -rf ./Descompacta
				rm -rf ./*.comp