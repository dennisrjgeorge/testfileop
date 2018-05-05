OUTPUT=test
LIB_DIR=lib
SRC_DIR=src
INC_DIR=inc
OBJ_DIR=obj
CC=gcc
CFLAGS=-Wall -g -I$(INC_DIR)
LFLAGS=-L$(LIB_DIR)

$(OUTPUT): $(OBJ_DIR)/main.o
	$(CC) $(LFLAGS) -o $@ $^

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -f $(OBJ_DIR)/*.o
	rm -f $(OUTPUT)
