SRC = ./src/
INC = ./include/
OBJ = ./obj/
BIN = ./bin/

CC = gcc
CFLAGS = -Wall -std=gnu11
EXEC = carcassonne

.PHONY: all run clean

all: $(EXEC)

run: $(EXEC)
	$(BIN)$<

$(EXEC): moteur_jeu.o fct_carcassonne.o
	$(CC) $(OBJ)* -I $(INC) -o $(BIN)$@
	
moteur_jeu.o: $(SRC)moteur_jeu.c
	$(CC) $(CFLAGS) $< -c -I $(INC) -o $(OBJ)$@

fct_carcassonne.o: $(SRC)fct_carcassonne.c
	$(CC) $(CFLAGS) $< -c -I $(INC) -o $(OBJ)$@

clean:
	rm $(BIN)* $(OBJ)*