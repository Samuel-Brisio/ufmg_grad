CXX = gcc
CFLAGS = -Wall -c
LIBS = -lm -pthread
BIN_FOLDER = bin
INC_FOLDER = include
OBJ_FOLDER = obj
SRC_FOLDER = src
CXXFLAGS = -Wall -c -I$(INC_FOLDER)

#especificar qual versão do compilador utilizar

PROGRAM_OBJS = $(OBJ_FOLDER)/spend_time.o $(OBJ_FOLDER)/ep1_main.o
RAPHA_PROGRAM = $(OBJ_FOLDER)/spend_time.o $(OBJ_FOLDER)/rapha_ep1_main.o

HDRS = $(wildcard $(INC_FOLDER)/*.h) $(wildcard $(INC_FOLDER)/*.hpp)
SRCS = $(wildcard $(SRC_FOLDER)/*.cpp) $(wildcard $(SRC_FOLDER)/*.c)

EXE = $(BIN_FOLDER)/ep1_main $(BIN_FOLDER)/rapha

all: $(EXE)

$(BIN_FOLDER)/ep1_main: $(HDRS) $(PROGRAM_OBJS)
	$(CXX) -g -o $(BIN_FOLDER)/ep1_main $(PROGRAM_OBJS) $(LIBS)

$(BIN_FOLDER)/rapha: $(HDRS) $(RAPHA_PROGRAM)
	$(CXX) -g -o $(BIN_FOLDER)/rapha $(RAPHA_PROGRAM) $(LIBS)

$(OBJ_FOLDER)/ep1_main.o: $(HDRS) $(SRCS)
	$(CXX) -g $(CXXFLAGS) -o $(OBJ_FOLDER)/ep1_main.o $(SRC_FOLDER)/ep1_main.c

$(OBJ_FOLDER)/rapha_ep1_main.o: $(HDRS) $(SRCS)
	$(CXX) -g $(CXXFLAGS) -o $(OBJ_FOLDER)/rapha_ep1_main.o $(SRC_FOLDER)/Rapha_ep1_main.c

$(OBJ_FOLDER)/spend_time.o: $(HDRS) $(SRCS)
	$(CXX) -g $(CXXFLAGS) -o $(OBJ_FOLDER)/spend_time.o $(SRC_FOLDER)/spend_time.c


clean:
	rm $(BIN_FOLDER)/* $(OBJ_FOLDER)/* 