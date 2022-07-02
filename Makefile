# OBJS specifies which files to compile as part of the project
OBJS = unitc.c

# OBJ_NAME specifies the name of the object file
OBJ_NAME = unitc.o

# This is the target that compiles and archives the object files into a 
# static library
lib: $(OBJ)
	gcc $(OBJS) -o $(OBJ_NAME) -c -Wall -Werror -Wpedantic
	sudo ar rcs /usr/local/lib/libunitc.a $(OBJ_NAME)
	sudo cp unitc.h /usr/local/include/unitc.h
	rm $(OBJ_NAME)
