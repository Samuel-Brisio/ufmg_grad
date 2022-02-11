CXX = g++
CFLAGS = -Wall -c
LIBS = -lm
BIN_FOLDER = bin
INC_FOLDER = include
OBJ_FOLDER = obj
SRC_FOLDER = src
CXXFLAGS = -Wall -c -I$(INC_FOLDER)

OBJS = $(OBJ_FOLDER)/main.o $(OBJ_FOLDER)/memlog.o
HDRS = $(wildcard $(INC_FOLDER)/*.h) $(wildcard $(INC_FOLDER)/*.hpp)
SRCS = $(wildcard $(SRC_FOLDER)/*.cpp) $(wildcard $(SRC_FOLDER)/*.c)

EXE = $(BIN_FOLDER)/programa

all: $(EXE)

$(BIN_FOLDER)/programa: $(HDRS) $(OBJS)
	$(CXX) -g -o $(BIN_FOLDER)/programa $(OBJS) $(LIBS)

$(OBJ_FOLDER)/main.o: $(HDRS) $(SRCS)
	$(CXX) -g $(CXXFLAGS) -o $(OBJ_FOLDER)/main.o $(SRC_FOLDER)/main.cpp

$(OBJ_FOLDER)/memlog.o: $(HDRS) $(SRCS)
	$(CXX) -g $(CXXFLAGS) -o $(OBJ_FOLDER)/memlog.o $(SRC_FOLDER)/memlog.c

clean:
	rm $(BIN_FOLDER)/* $(OBJ_FOLDER)/* 