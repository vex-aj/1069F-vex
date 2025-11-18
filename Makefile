# Makefile for VEX V5 Robot Project
# Supports both robot code and unit tests

# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

# Directories
SRC_DIR = src
CONTROLLERS_DIR = src/controllers
TEST_DIR = tests
BUILD_DIR = build

# Robot code (for VEX V5 - would need PROS toolchain in real project)
ROBOT_SOURCES = $(SRC_DIR)/main.cpp $(CONTROLLERS_DIR)/DriveTrain.cpp
ROBOT_OBJECTS = $(ROBOT_SOURCES:%.cpp=$(BUILD_DIR)/%.o)
ROBOT_TARGET = robot_code

# Test sources
TEST_SOURCES = $(TEST_DIR)/test_drivetrain.cpp $(TEST_DIR)/test_intakecontroller.cpp $(TEST_DIR)/test_rampcontroller.cpp $(TEST_DIR)/test_pneumaticcontroller.cpp
TEST_TARGET = $(BUILD_DIR)/test_runner
INTAKE_TEST_TARGET = $(BUILD_DIR)/test_intake_runner
RAMP_TEST_TARGET = $(BUILD_DIR)/test_ramp_runner
PNEUMATIC_TEST_TARGET = $(BUILD_DIR)/test_pneumatic_runner

.PHONY: all clean test robot

# Default: build tests
all: test

# Build and run all tests
test: $(TEST_TARGET) $(INTAKE_TEST_TARGET) $(RAMP_TEST_TARGET) $(PNEUMATIC_TEST_TARGET)
	@echo "Running DriveTrain unit tests..."
	@./$(TEST_TARGET)
	@echo "\nRunning IntakeController unit tests..."
	@./$(INTAKE_TEST_TARGET)
	@echo "\nRunning RampController unit tests..."
	@./$(RAMP_TEST_TARGET)
	@echo "\nRunning PneumaticController unit tests..."
	@./$(PNEUMATIC_TEST_TARGET)

# Build test runners
$(TEST_TARGET): $(TEST_DIR)/test_drivetrain.cpp $(CONTROLLERS_DIR)/DriveTrain.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(SRC_DIR) -o $(TEST_TARGET) $(TEST_DIR)/test_drivetrain.cpp $(CONTROLLERS_DIR)/DriveTrain.cpp

$(INTAKE_TEST_TARGET): $(TEST_DIR)/test_intakecontroller.cpp $(CONTROLLERS_DIR)/IntakeController.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(SRC_DIR) -o $(INTAKE_TEST_TARGET) $(TEST_DIR)/test_intakecontroller.cpp $(CONTROLLERS_DIR)/IntakeController.cpp

$(RAMP_TEST_TARGET): $(TEST_DIR)/test_rampcontroller.cpp $(CONTROLLERS_DIR)/RampController.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(SRC_DIR) -o $(RAMP_TEST_TARGET) $(TEST_DIR)/test_rampcontroller.cpp $(CONTROLLERS_DIR)/RampController.cpp

$(PNEUMATIC_TEST_TARGET): $(TEST_DIR)/test_pneumaticcontroller.cpp $(CONTROLLERS_DIR)/PneumaticController.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(SRC_DIR) -o $(PNEUMATIC_TEST_TARGET) $(TEST_DIR)/test_pneumaticcontroller.cpp $(CONTROLLERS_DIR)/PneumaticController.cpp


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

