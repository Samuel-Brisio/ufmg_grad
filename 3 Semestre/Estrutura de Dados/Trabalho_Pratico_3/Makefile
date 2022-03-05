CXX = g++
CFLAGS = -Wall -c
LIBS = -lm
BIN_FOLDER = bin
INC_FOLDER = include
OBJ_FOLDER = obj
SRC_FOLDER = src
CXXFLAGS = -Wall -c -I$(INC_FOLDER)

#especificar qual versão do compilador utilizar

OBJS = $(OBJ_FOLDER)/main.o $(OBJ_FOLDER)/memlog.o $(OBJ_FOLDER)/structs.o $(OBJ_FOLDER)/hash.o
HDRS = $(wildcard $(INC_FOLDER)/*.h) $(wildcard $(INC_FOLDER)/*.hpp)
SRCS = $(wildcard $(SRC_FOLDER)/*.cpp) $(wildcard $(SRC_FOLDER)/*.c)

EXE = $(BIN_FOLDER)/program

all: $(EXE)

$(BIN_FOLDER)/program: $(HDRS) $(OBJS)
	$(CXX) -g -o $(BIN_FOLDER)/program $(OBJS) $(LIBS)

$(OBJ_FOLDER)/main.o: $(HDRS) $(SRCS)
	$(CXX) -g $(CXXFLAGS) -o $(OBJ_FOLDER)/main.o $(SRC_FOLDER)/main.cpp

$(OBJ_FOLDER)/memlog.o: $(HDRS) $(SRCS)
	$(CXX) -g $(CXXFLAGS) -o $(OBJ_FOLDER)/memlog.o $(SRC_FOLDER)/memlog.c

$(OBJ_FOLDER)/structs.o: $(HDRS) $(SRCS)
	$(CXX) -g $(CXXFLAGS) -o $(OBJ_FOLDER)/structs.o $(SRC_FOLDER)/structs.cpp

$(OBJ_FOLDER)/hash.o: $(HDRS) $(SRCS)
	$(CXX) -g $(CXXFLAGS) -o $(OBJ_FOLDER)/hash.o $(SRC_FOLDER)/hash.cpp

clean:
	rm $(BIN_FOLDER)/* $(OBJ_FOLDER)/* Processo/*