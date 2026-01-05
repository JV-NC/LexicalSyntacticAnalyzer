# ===============================
# Default input file
# ===============================
INPUT ?= data/DomCasmurro.txt

# ===============================
# System
# ===============================
ifeq ($(OS),Windows_NT)
    TARGET = LSA.exe
    PYTHON = python
    RM = rmdir /S /Q
    MKDIR = mkdir
    SEP = \\
else
    TARGET = LSA
    PYTHON = python3
    RM = rm -rf
    MKDIR = mkdir -p
    SEP = /
endif

# ===============================
# Compiler
# ===============================
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -Iinclude

# ===============================
# Directories
# ===============================
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
OUT_DIR = output
UTILS_DIR = utils

# ===============================
# Files
# ===============================
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# ===============================
# Standard rule
# ===============================
all: dirs $(BIN_DIR)/$(TARGET)

# ===============================
# Make directories
# ===============================
dirs:
ifeq ($(OS),Windows_NT)
	@if not exist $(OBJ_DIR) $(MKDIR) $(OBJ_DIR)
	@if not exist $(BIN_DIR) $(MKDIR) $(BIN_DIR)
	@if not exist $(OUT_DIR) $(MKDIR) $(OUT_DIR)
else
	$(MKDIR) $(OBJ_DIR) $(BIN_DIR) $(OUT_DIR)
endif

# ===============================
# Linking
# ===============================
$(BIN_DIR)/$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# ===============================
# Compilation
# ===============================
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ===============================
# Execute analysis
# ===============================
run: all
	./$(BIN_DIR)/$(TARGET) $(INPUT)

# ===============================
# Generate plots
# ===============================
plots: run
	$(PYTHON) $(UTILS_DIR)$(SEP)plot_length_dist.py
	$(PYTHON) $(UTILS_DIR)$(SEP)plot_sort_metrics.py

# ===============================
# Cleaning
# ===============================
clean:
ifeq ($(OS),Windows_NT)
	@if exist $(OBJ_DIR) $(RM) $(OBJ_DIR)
	@if exist $(BIN_DIR) $(RM) $(BIN_DIR)
	@if exist $(OUT_DIR) $(RM) $(OUT_DIR)
else
	$(RM) $(OBJ_DIR) $(BIN_DIR) $(OUT_DIR)
endif

# ===============================
# Execute all
# ===============================
full: clean run plots

.PHONY: all run plots full clean dirs