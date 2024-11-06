SRC = src
OBJ = obj
# LIB = lib

CC = gcc
CFLAGS = -Wall -c -Iinclude
EXE = carcassonne
OBJ_FILES = $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(wildcard $(SRC)/*.c))
INC_FILES = $(wildcard include/*.hpp)

.PHONY: all run clean

all: $(EXE)

run: $(EXE)
	./$<

$(EXE): $(OBJ_FILES)
	$(CC) $^ -o $@
	@echo "\nTappez ./$@ pour exécuter"
	
$(OBJ)/%.o: $(SRC)/%.c $(INC_FILES)
	$(CC) $(CFLAGS) $< -o $@

$(OBJ):
	mkdir -p $(OBJ)

clean:
	rm -f $(EXE) $(OBJ)/*