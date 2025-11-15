# Makefile for VEX V5 Robot Project
# Supports both robot code and unit tests

# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

# Directories
SRC_DIR = .
TEST_DIR = tests
BUILD_DIR = build

# Robot code (for VEX V5 - would need PROS toolchain in real project)
ROBOT_SOURCES = main.cpp DriveTrain.cpp
ROBOT_OBJECTS = $(ROBOT_SOURCES:%.cpp=$(BUILD_DIR)/%.o)
ROBOT_TARGET = robot_code

# Test sources
TEST_SOURCES = $(TEST_DIR)/test_drivetrain.cpp
TEST_TARGET = $(BUILD_DIR)/test_runner

.PHONY: all clean test robot

# Default: build tests
all: test

# Build and run tests
test: $(TEST_TARGET)
	@echo "Running unit tests..."
	@./$(TEST_TARGET)

# Build test runner
$(TEST_TARGET): $(TEST_DIR)/test_drivetrain.cpp DriveTrain.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_DIR)/test_drivetrain.cpp DriveTrain.cpp

# Build robot code (placeholder - real VEX uses PROS toolchain)
robot: $(ROBOT_TARGET)

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)
	rm -f $(ROBOT_TARGET)

# Help target
help:
	@echo "Available targets:"
	@echo "  make test    - Build and run unit tests"
	@echo "  make robot   - Build robot code (PROS toolchain needed)"
	@echo "  make clean   - Remove build artifacts"
	@echo "  make help    - Show this help message"

