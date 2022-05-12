BIN_FOLDER = bin
INCLUDE_FOLDER = include
OBJ_FOLDER = obj
SRC_FOLDER = src

GXX = g++
GXXFLAGS = -g -Wall -c -I$(INCLUDE_FOLDER)/
LIBS = -lm

OBJS = $(OBJ_FOLDER)/main.o $(OBJ_FOLDER)/gs.o $(OBJ_FOLDER)/bfs.o
HDRS = $(wildcard $(INCLUDE_FOLDER)/*.hpp)
SRCS = $(wildcard $(SRC_FOLDER)/*.cpp)

EXE = $(BIN_FOLDER)/main

all: $(EXE)

$(BIN_FOLDER)/main: $(HDRS) $(OBJS)
	$(GXX) -o $(BIN_FOLDER)/main $(OBJS) $(LIBS)

$(OBJ_FOLDER)/main.o: $(HDRS) $(SRC_FOLDER)/main.cpp
	$(GXX) $(GXXFLAGS) -o $(OBJ_FOLDER)/main.o $(SRC_FOLDER)/main.cpp

$(OBJ_FOLDER)/gs.o: $(HDRS) $(SRC_FOLDER)/gs.cpp
	$(GXX) $(GXXFLAGS) -o $(OBJ_FOLDER)/gs.o $(SRC_FOLDER)/gs.cpp 

$(OBJ_FOLDER)/bfs.o: $(HDRS) $(SRC_FOLDER)/bfs.cpp
	$(GXX) $(GXXFLAGS) -o $(OBJ_FOLDER)/bfs.o $(SRC_FOLDER)/bfs.cpp

clean:
	rm $(BIN_FOLDER)/* $(OBJ_FOLDER)/*