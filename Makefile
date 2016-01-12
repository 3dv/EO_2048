#Copyright Notice:
#The files within this zip file are copyrighted by Lazy Foo' Productions (2004-2014)
#and may not be redistributed without written permission.

#OBJS specifies which files to compile as part of the project
OBJS = casilla.cpp juego.cpp tablero.cpp main.cpp

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w -g 

#LINKER_FLAGS specifies the libraries we're linking against
#LINKER_FLAGS = "-lSDL"

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = juego2048

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS)  -o $(OBJ_NAME) #$(LINKER_FLAGS)
