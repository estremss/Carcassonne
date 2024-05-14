SRC = ./src/
INC = ./include/
OBJ = ./obj/
BIN = ./bin/
LIB = ./lib/

CC = gcc
CFLAGS = -Wall -std=gnu11
EXEC = carcassonne
LIBS = $(LIB)libraylib.a

.PHONY: all run clean

all: $(EXEC)

run: $(EXEC)
	$(BIN)$<

$(EXEC): moteur_jeu.o fct_carcassonne.o affichage.o ia.o
	$(CC) $(OBJ)* $(LIBS) -I $(INC) -o $(BIN)$@ -lm
	
moteur_jeu.o: $(SRC)moteur_jeu.c
	$(CC) $(CFLAGS) $< -c -I $(INC) -o $(OBJ)$@

fct_carcassonne.o: $(SRC)fct_carcassonne.c
	$(CC) $(CFLAGS) $< -c -I $(INC) -o $(OBJ)$@

affichage.o: $(SRC)affichage.c
	$(CC) $(CFLAGS) $< -c -I $(INC) -o $(OBJ)$@

ia.o: $(SRC)ia.c
	$(CC) $(CFLAGS) $< -c -I $(INC) -o $(OBJ)$@

clean:
	rm $(BIN)* $(OBJ)*