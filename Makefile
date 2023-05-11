CC = gcc
CFLAGS =-Wall -lstdc++ -lm
LDFLAGS =-lsfml-graphics -lsfml-window -lsfml-system
SRC = src
OBJ = obj
SRCS = $(wildcard $(SRC)/*.cpp) $(wildcard $(SRC)/states/*.cpp)
OBJS = $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRCS))
HEADERS = $(SRC)/include/
BIN_DIR = bin
BIN = $(BIN_DIR)/maze_generator

all: $(BIN)
$(BIN): $(OBJS) | structure
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)
$(OBJ)/%.o: $(SRC)/%.cpp $(HEADERS)/%.hpp | structure
	$(CC) $(CFLAGS) -c $< -o $@	$(LDFLAGS)

$(OBJ)/%.o: $(SRC)/%.cpp | structure
	$(CC) $(CFLAGS) -c $< -o $@	$(LDFLAGS)

structure:
	mkdir -p  $(OBJ)/states $(BIN_DIR)
run: all
	./$(BIN)
clean:
	rm -rf $(BIN_DIR)/* $(OBJ)/*
