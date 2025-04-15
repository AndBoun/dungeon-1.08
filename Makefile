CXX = g++
CXXFLAGS = -g -Wall -Werror -std=c++17
CC = gcc
CFLAGS = -g -Wall -Werror
INCLUDE_DIR = include
SRC_DIR = src
OBJ_DIR = obj
LDFLAGS = -lncurses

# Create directory structure for object files
DIRS = $(OBJ_DIR) $(OBJ_DIR)/dungeon $(OBJ_DIR)/dungeon/base $(OBJ_DIR)/utils $(OBJ_DIR)/io $(OBJ_DIR)/character $(OBJ_DIR)/pathfinding $(OBJ_DIR)/movement $(OBJ_DIR)/ui $(OBJ_DIR)/item

# Source files
DUNGEON_SRC = $(wildcard $(SRC_DIR)/dungeon/*.cpp)
DUNGEON_BASE_SRC = $(wildcard $(SRC_DIR)/dungeon/base/*.cpp)
IO_SRC = $(wildcard $(SRC_DIR)/io/*.cpp)
UTILS_CPP_SRC = $(wildcard $(SRC_DIR)/utils/*.cpp)
UTILS_C_SRC = $(wildcard $(SRC_DIR)/utils/*.c)
CHARACTER_SRC = $(wildcard $(SRC_DIR)/character/*.cpp)
PATHFINDING_SRC = $(wildcard $(SRC_DIR)/pathfinding/*.cpp)
MOVEMENT_SRC = $(wildcard $(SRC_DIR)/movement/*.cpp)
UI_SRC = $(wildcard $(SRC_DIR)/ui/*.cpp)
ITEM_SRC = $(wildcard $(SRC_DIR)/item/*.cpp)
MAIN_SRC = $(SRC_DIR)/main.cpp

# Object files
DUNGEON_OBJ = $(patsubst $(SRC_DIR)/dungeon/%.cpp, $(OBJ_DIR)/dungeon/%.o, $(DUNGEON_SRC))
DUNGEON_BASE_OBJ = $(patsubst $(SRC_DIR)/dungeon/base/%.cpp, $(OBJ_DIR)/dungeon/base/%.o, $(DUNGEON_BASE_SRC))
IO_OBJ = $(patsubst $(SRC_DIR)/io/%.cpp, $(OBJ_DIR)/io/%.o, $(IO_SRC))
UTILS_CPP_OBJ = $(patsubst $(SRC_DIR)/utils/%.cpp, $(OBJ_DIR)/utils/%.o, $(UTILS_CPP_SRC))
UTILS_C_OBJ = $(patsubst $(SRC_DIR)/utils/%.c, $(OBJ_DIR)/utils/%.o, $(UTILS_C_SRC))
CHARACTER_OBJ = $(patsubst $(SRC_DIR)/character/%.cpp, $(OBJ_DIR)/character/%.o, $(CHARACTER_SRC))
PATHFINDING_OBJ = $(patsubst $(SRC_DIR)/pathfinding/%.cpp, $(OBJ_DIR)/pathfinding/%.o, $(PATHFINDING_SRC))
MOVEMENT_OBJ = $(patsubst $(SRC_DIR)/movement/%.cpp, $(OBJ_DIR)/movement/%.o, $(MOVEMENT_SRC))
UI_OBJ = $(patsubst $(SRC_DIR)/ui/%.cpp, $(OBJ_DIR)/ui/%.o, $(UI_SRC))
ITEM_OBJ = $(patsubst $(SRC_DIR)/item/%.cpp, $(OBJ_DIR)/item/%.o, $(ITEM_SRC))
MAIN_OBJ = $(OBJ_DIR)/main.o

# All objects
ALL_OBJ = $(DUNGEON_OBJ) $(DUNGEON_BASE_OBJ) $(IO_OBJ) $(UTILS_CPP_OBJ) $(UTILS_C_OBJ) $(CHARACTER_OBJ) $(PATHFINDING_OBJ) $(MOVEMENT_OBJ) $(UI_OBJ) $(ITEM_OBJ) $(MAIN_OBJ)

# Target executable
TARGET = dungeon

all: dirs $(TARGET)

dirs:
	@mkdir -p $(DIRS)

$(TARGET): $(ALL_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Compile main.cpp
$(OBJ_DIR)/main.o: $(MAIN_SRC)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Compile dungeon files
$(OBJ_DIR)/dungeon/%.o: $(SRC_DIR)/dungeon/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Compile dungeon/base files
$(OBJ_DIR)/dungeon/base/%.o: $(SRC_DIR)/dungeon/base/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Compile io files
$(OBJ_DIR)/io/%.o: $(SRC_DIR)/io/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Compile utils C files
$(OBJ_DIR)/utils/%.o: $(SRC_DIR)/utils/%.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Compile utils C++ files
$(OBJ_DIR)/utils/%.o: $(SRC_DIR)/utils/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Compile character files
$(OBJ_DIR)/character/%.o: $(SRC_DIR)/character/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Compile pathfinding files
$(OBJ_DIR)/pathfinding/%.o: $(SRC_DIR)/pathfinding/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Compile movement files
$(OBJ_DIR)/movement/%.o: $(SRC_DIR)/movement/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Compile ui files
$(OBJ_DIR)/ui/%.o: $(SRC_DIR)/ui/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Compile item files
$(OBJ_DIR)/item/%.o: $(SRC_DIR)/item/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all dirs clean