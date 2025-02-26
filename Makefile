# Nom de l'exécutable
TARGET = ./bin/skylab

# Répertoires
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = includes

# Compilateurs
CC = gcc
CXX = g++

# Options de compilation
CFLAGS = -Wall -Wextra -I$(INC_DIR)
CXXFLAGS = -Wall -Wextra -std=c++17 -I$(INC_DIR) `pkg-config --cflags freetype2`
LDFLAGS = -lfmt -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lfreetype

# Recherche récursive des fichiers sources
SRC_C = $(shell find $(SRC_DIR) -type f -name "*.c")
SRC_CPP = $(shell find $(SRC_DIR) -type f -name "*.cpp")

# Création des chemins des fichiers objets en conservant l'arborescence
OBJ_C = $(SRC_C:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ_CPP = $(SRC_CPP:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
OBJECTS = $(OBJ_C) $(OBJ_CPP)

all: $(TARGET)

# Règle principale
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# Compilation des fichiers .c
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Compilation des fichiers .cpp
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Création du dossier obj/ s'il n'existe pas
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Nettoyage
clean:
	rm -rf $(OBJ_DIR) bin
	mkdir bin

rebuild: clean all

