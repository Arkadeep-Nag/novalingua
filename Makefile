# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Iinclude

# Source files and object files
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:src/%.cpp=build/%.o)
INCLUDE = $(wildcard include/*.hpp)

# Target executable
TARGET = novalingua

# Default rule
all: $(TARGET)

# Link the object files to create the final executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files
build/%.o: src/%.cpp $(INCLUDE)
	mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean the build artifacts
clean:
	rm -rf build $(TARGET)
