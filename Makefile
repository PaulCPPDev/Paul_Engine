################################################################################
# Declare some Makefile variables
################################################################################
CC = g++
LANG_STD = -std=c++17
COMPILER_FLAGS = -Wall -Wfatal-errors
INCLUDE_PATH = -I"./libs/"
SRC_FILES = ./Core/main.cpp \
	    ./Core/*/*.cpp \
	    ./Renderer/Graphics.cpp

LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llua5.3 
OBJ_NAME = paulengine

################################################################################
# Declare some Makefile rules
################################################################################
build:
	$(CC) $(COMPILER_FLAGS) $(LANG_STD) $(INCLUDE_PATH) $(SRC_FILES) $(LINKER_FLAGS) -o $(OBJ_NAME)

run:
	./$(OBJ_NAME)

clean:
	rm $(OBJ_NAME)
