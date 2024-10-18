CC=cc
CFLAGS=-Wall -Wextra -Werror
LIB=lib
SRC_DIR=src
OBJ_DIR=obj
TARGET=myowndb

SRC=$(wildcard $(SRC_DIR)/*.c)
OBJ=$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c lib/main.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

mrproper: clean
	rm -rf $(TARGET)

.PHONY: all clean mrproper