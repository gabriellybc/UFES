### MAKEFILE ###
## Gabrielly Barcelos Cariman ##
## Lara De Luca Mota Teixeira ##

all:
				gcc  main.c macaco_ponte.c -pthread -o prog.o
				
clean:
				rm -rf ./*.o

valgrind:
				gcc  main.c macaco_ponte.c -pthread -o prog.o
				valgrind --leak-check=full --show-leak-kinds=all ./prog.o