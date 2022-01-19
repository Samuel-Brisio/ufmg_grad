CXX = g++
CFLAGS = -Wall -c
LIBS = -lm
BIN_FOLDER = bin
INC_FOLDER = include
OBJ_FOLDER = obj
SRC_FOLDER = src
CXXFLAGS = -Wall -c -I$(INC_FOLDER)

OBJS = $(OBJ_FOLDER)/main.o 
HDRS = $(wildcard $(INC_FOLDER)/*.h) $(wildcard $(INC_FOLDER)/*.hpp)
SRCS = $(wildcard $(SRC_FOLDER)/*.cpp)

EXE = $(BIN_FOLDER)/main
DEBUG = $(BIN_FOLDER)/debug

all: $(EXE)

$(BIN_FOLDER)/main: $(HDRS) $(OBJS)
	$(CXX) -o $(BIN_FOLDER)/main $(OBJS) $(LIBS)

$(OBJ_FOLDER)/main.o: $(HDRS) $(SRC_FOLDER)/main.cpp
	$(CXX) $(CXXFLAGS) -o $(OBJ_FOLDER)/main.o $(SRC_FOLDER)/main.cpp

debug: $(DEBUG)

$(BIN_FOLDER)/debug: $(HDRS) $(OBJ_FOLDER)/debug.o
	$(CXX) -g -o $(BIN_FOLDER)/debug $(OBJ_FOLDER)/debug.o $(LIBS)

$(OBJ_FOLDER)/debug.o: $(HDRS) $(SRCS)
	$(CXX) -g $(CXXFLAGS) -o $(OBJ_FOLDER)/debug.o $(SRC_FOLDER)/main.cpp

dexe:
	./$(DEBUG) < input.txt
	
clean:
	rm $(BIN_FOLDER)/* $(OBJ_FOLDER)/* 