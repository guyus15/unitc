CC = gcc

# OBJS specifies which files to compile as part of the project
OBJS = src/unitc.c

# OBJ_NAME specifies the name of the object file
OBJ_NAME = unitc.o

LIB_DIR = lib
LIB = libunitc

INCLUDE = include/

# This is the target that compiles and archives the object files into a 
# static library
install: $(OBJ)
	$(CC) $(OBJS) -o $(OBJ_NAME) -c -Wall -Werror -Wpedantic -lm -I $(INCLUDE)
	sudo ar rcs /usr/local/lib/libunitc.a $(OBJ_NAME)
	sudo cp include/unitc.h /usr/local/include/unitc.h
	rm $(OBJ_NAME)

build:
	mkdir -p $(LIB_DIR)
	$(CC) $(OBJS) -o $(OBJ_NAME) -c -Wall -Werror -Wpedantic -lm -I $(INCLUDE)
	ar rcs $(LIB_DIR)/$(LIB).a $(OBJ_NAME)
	rm $(OBJ_NAME)

all: build
