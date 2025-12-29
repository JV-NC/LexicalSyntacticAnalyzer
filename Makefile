# ===============================
# Sistema
# ===============================
ifeq ($(OS),Windows_NT)
    TARGET = LSA.exe
else
    TARGET = LSA
endif

# ===============================
# Compilador
# ===============================
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

# ===============================
# Diretórios
# ===============================
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
OUT_DIR = output

# ===============================
# Arquivos
# ===============================
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# ===============================
# Regra padrão
# ===============================
all: dirs $(BIN_DIR)/$(TARGET)

# ===============================
# Criar diretórios
# ===============================
dirs:
ifeq ($(OS),Windows_NT)
	@if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)
	@if not exist $(BIN_DIR) mkdir $(BIN_DIR)
	@if not exist $(OUT_DIR) mkdir $(OUT_DIR)
else
	mkdir -p $(OBJ_DIR) $(BIN_DIR) $(OUT_DIR)
endif

# ===============================
# Linkagem
# ===============================
$(BIN_DIR)/$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# ===============================
# Compilação
# ===============================
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ===============================
# Executar
# ===============================
run: all
	./$(BIN_DIR)/$(TARGET)

# ===============================
# Limpeza
# ===============================
clean:
ifeq ($(OS),Windows_NT)
	@if exist $(OBJ_DIR) rmdir /S /Q $(OBJ_DIR)
	@if exist $(BIN_DIR) rmdir /S /Q $(BIN_DIR)
	@if exist $(OUT_DIR) rmdir /S /Q $(OUT_DIR)
else
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(OUT_DIR)
endif

.PHONY: all run clean dirs