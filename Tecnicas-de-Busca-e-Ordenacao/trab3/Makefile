### MAKEFILE ###

all:
				gcc *.c -o trab3 -lm 

clean:
				rm -f trab3 *.o a.out

run:
				gcc *.c -o trab3 -lm
				./trab3 entrada.txt saida.txt

val:
				gcc *.c -o trab3 -lm 
				valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./trab3 teste3/TBO-20240920T021340Z-001/TBO/luiz-sample-large < teste3/TBO-20240920T021340Z-001/TBO/luiz-sample-large/searches.txt >arq.txt
				