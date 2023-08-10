### MAKEFILE ###
## Gabrielly Barcelos Cariman ##
## Lara De Luca Mota Teixeira ##

all:
				gcc leitor_cmd.c exec_cmd.c main.c -o prog.o
				
clean:
				rm -rf ./*.o

valgrind:
				gcc leitor_cmd.c exec_cmd.c main.c -o prog.o
				valgrind --leak-check=full --show-leak-kinds=all ./prog.o