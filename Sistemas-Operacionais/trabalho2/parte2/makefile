### MAKEFILE ###
## Gabrielly Barcelos Cariman ##
## Lara De Luca Mota Teixeira ##

all:
				gcc MonitorBanheiro.c Funcionarios.c -lpthread -o prog.o

				
clean:
				rm -rf ./*.o

valgrind:
				gcc  main.c MonitorBanheiro.c Funcionarios.c -lpthread -o prog.o
				valgrind --leak-check=full --show-leak-kinds=all ./prog.o