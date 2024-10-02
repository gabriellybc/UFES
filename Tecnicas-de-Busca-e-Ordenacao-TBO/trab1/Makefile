# Name of the project
PROJ_NAME=trab1

# main file
MAIN_FILE=./source/main.c

# main object file
MAIN_OBJ=$(subst .c,.o,$(subst source,objects,$(MAIN_FILE)))

# main parameters
MAIN_PARAM=entrada.txt 3 saida.txt
 
# .c files
C_SOURCE=$(wildcard ./source/*.c)
 
# .h files
H_SOURCE=$(wildcard ./source/*.h)
 
# Object files
OBJ=$(subst .c,.o,$(subst source,objects,$(C_SOURCE)))
 
# Compiler and linker
CC=gcc
 
# Flags for compiler (identação com espaço, sem tab)
CC_FLAGS=-c     \
         -g

#Flags for linker
LINK_FLAGS=-lm

#Parameters for valgrind (identação com espaço, sem tab)
VALGRIND_PARAM=--leak-check=full    \
               -s
# Command used at clean target
RM = rm -rf
 
#
# Compilation and linking
#
all: objFolder $(PROJ_NAME)
 
$(PROJ_NAME): $(OBJ)
	@ echo 'Building binary using GCC linker: $@'
	$(CC) $^ -o $@ $(LINK_FLAGS)
	@ echo 'Finished building binary: $@'
	@ echo ' '
 
./objects/%.o: ./source/%.c ./source/%.h
	@ echo 'Building target using GCC compiler: $<'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '
 
./$(MAIN_OBJ): $(MAIN_FILE) $(H_SOURCE)
	@ echo 'Building target using GCC compiler: $<'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '
 
objFolder:
	@ mkdir -p objects
 
clean:
	@ $(RM) ./objects/*.o $(PROJ_NAME) *~
	@ rmdir objects

valgrind: objFolder $(PROJ_NAME)
	valgrind $(VALGRIND_PARAM) ./$(PROJ_NAME) $(MAIN_PARAM)

run: objFolder $(PROJ_NAME)
	./$(PROJ_NAME) $(MAIN_PARAM)

.PHONY: all clean valgrind run