# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

# Paths for source, header, and build
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include

# Source files and object files
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Target executable
TARGET = novalingua

# Default rule
all: $(TARGET)

# Link the object files to create the final executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(wildcard $(INCLUDE_DIR)/*.hpp)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the program with a test file
test: $(TARGET)
	./$(TARGET) examples/test.nol

# Clean the build artifacts
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Print useful info for debugging the Makefile
info:
	@echo "Source files: $(SRC)"
	@echo "Object files: $(OBJ)"
	@echo "Headers: $(wildcard $(INCLUDE_DIR)/*.hpp)"

.PHONY: all clean test info
