# Project Summary - VEX V5 Robot with TDD

## 🎯 What This Project Does

This is a **VEX V5 robotics project** that shows how to control a robot's drive train (the motors that make it move) using **Test-Driven Development (TDD)**. 

The robot can be driven in two ways:
1. **Tank Drive**: Left stick controls left motors, right stick controls right motors (like a tank)
2. **Arcade Drive**: One stick controls forward/backward and left/right turning (like a car) - commented out but ready to use

---

## 📁 Project Files Explained

### **Robot Code (Hardware Interface)**

#### `main.cpp` - The Robot's Main Program
- **What it does**: Controls the actual robot hardware
- **Key parts**:
  - Declares motors (LeftFrontMotor, LeftBackMotor, RightFrontMotor, RightBackMotor)
  - Groups motors together (LeftDrive, RightDrive)
  - Connects to the VEX controller
  - Has two modes:
    - `autonomous()` - Robot runs by itself (example: drives forward for 2 seconds)
    - `usercontrol()` - Driver controls the robot using the controller
- **Current setup**: Uses Tank Drive by reading controller sticks and calling `DriveTrain` functions

#### `main.h` - Header File
- **What it does**: Includes VEX library and standard headers
- **Purpose**: Provides access to VEX robot functions

---

### **Logic Layer (Testable Code)**

#### `DriveTrain.h` & `DriveTrain.cpp` - Drive Train Logic
- **What it does**: Contains all the *thinking* about how to drive, separated from hardware
- **Why separate**: Can test this code without needing actual motors!
- **Key functions**:
  
  1. **`calculateTankDrive()`**
     - Input: Left stick value, right stick value
     - Output: Left motor power, right motor power
     - Logic: Left stick → left motors, right stick → right motors (simple!)
  
  2. **`calculateArcadeDrive()`**
     - Input: Forward/backward value, turn left/right value
     - Output: Left motor power, right motor power
     - Logic: 
       - Left motor = forward + turn
       - Right motor = forward - turn
       - Example: Forward 50%, turn right 25% → Left 75%, Right 25%
  
  3. **`clamp()`**
     - Input: A value, min limit, max limit
     - Output: Value clamped to limits (-100 to 100)
     - Purpose: Prevents motor powers from exceeding limits
  
  4. **`applyDeadband()`**
     - Input: Controller value, deadband threshold
     - Output: Controller value or 0
     - Purpose: Prevents tiny controller drift from moving the robot
     - Example: If input is 3 and deadband is 5 → returns 0 (ignores drift)

**Why this matters**: These are **pure functions** - same input always gives same output, no hardware needed to test!

---

### **Test Layer**

#### `tests/test_drivetrain.cpp` - Unit Tests
- **What it does**: Tests all the DriveTrain functions to make sure they work correctly
- **Contains**:
  1. **Simple test framework** (`TestRunner` class)
     - `assertEquals()` - Compares expected vs actual values
     - `assertTrue()` - Checks if something is true
     - `printResults()` - Shows test summary
  2. **20 test cases** covering:
     - Tank drive (forward, reverse, turning)
     - Arcade drive (forward, turning, edge cases)
     - Clamping (boundary conditions)
     - Deadband (drift prevention)
- **How to run**: `make test` or compile manually

**Example test structure** (AAA Pattern):
```cpp
void testArcadeDrive_TurnRight() {
    // ARRANGE: Set up test data
    int forwardInput = 50;
    int turnInput = 25;
    int leftPower, rightPower;
    
    // ACT: Execute the function
    DriveTrain::calculateArcadeDrive(forwardInput, turnInput, leftPower, rightPower);
    
    // ASSERT: Verify results
    TestRunner::assertEquals(75, leftPower, "Left motor faster");
    TestRunner::assertEquals(25, rightPower, "Right motor slower");
}
```

---

### **Build System**

#### `Makefile` - Build Configuration
- **What it does**: Makes it easy to compile and run tests
- **Commands**:
  - `make test` - Compiles and runs all tests
  - `make clean` - Removes build files
  - `make help` - Shows available commands

---

### **Documentation**

#### `README.md` - Quick Start Guide
- Overview of the project
- How to run tests
- Key features and architecture

#### `TDD_GUIDE.md` - Comprehensive TDD Guide
- What is TDD (RED-GREEN-REFACTOR cycle)
- Why TDD for robotics
- Best practices
- Testing frameworks comparison
- Examples and workflows

---

## 🏗️ Architecture Overview

### The Key Design Pattern: **Separation of Concerns**

```
┌─────────────────────────────────────┐
│  Hardware Layer (main.cpp)          │
│  - Motors, controller, brain        │
│  - Controls actual robot            │
└──────────────┬──────────────────────┘
               │ calls
               ↓
┌─────────────────────────────────────┐
│  Logic Layer (DriveTrain.cpp)       │
│  - Pure functions                   │
│  - No hardware dependencies         │
│  - Easy to test!                    │
└──────────────┬──────────────────────┘
               ↑
               │ tested by
┌─────────────────────────────────────┐
│  Test Layer (test_drivetrain.cpp)   │
│  - Unit tests                       │
│  - No hardware needed               │
│  - Runs in seconds                  │
└─────────────────────────────────────┘
```

### Why This Design?

**Before (Hard to Test)**:
```cpp
// Everything mixed together in main.cpp
void usercontrol() {
    LeftDrive.spin(forward, Controller1.Axis3.position(), percent);
    RightDrive.spin(forward, Controller1.Axis2.position(), percent);
}
// ❌ Can't test without robot hardware
```

**After (Easy to Test)**:
```cpp
// In main.cpp
int leftPower, rightPower;
DriveTrain::calculateTankDrive(leftStick, rightStick, leftPower, rightPower);
LeftDrive.spin(forward, leftPower, percent);

// In DriveTrain.cpp (pure function - testable!)
void calculateTankDrive(int left, int right, int& leftPower, int& rightPower) {
    leftPower = left;
    rightPower = right;
}
// ✅ Can test DriveTrain logic without motors!
```

---

## 🧪 Test-Driven Development (TDD) Workflow

### The RED-GREEN-REFACTOR Cycle

1. **RED** 🔴
   - Write a test first (it will fail because code doesn't exist yet)
   - Example: `testClamp_AboveMaximum()` expects clamp(150, -100, 100) = 100
   - Run test → ❌ FAILS (clamp function doesn't exist)

2. **GREEN** 🟢
   - Write minimal code to make test pass
   - Example: Create `clamp()` function that returns min(max, value)
   - Run test → ✅ PASSES

3. **REFACTOR** ♻️
   - Improve code quality while keeping tests passing
   - Example: Clean up clamp() logic, add comments
   - Run tests → ✅ Still passing!

**Repeat** this cycle for each new feature!

---

## 📊 What the Tests Cover

### ✅ 20 Test Cases Total:

**Tank Drive Tests:**
- Forward movement (50%, 50%)
- Reverse movement (-50%, -50%)
- Turning left (-50%, 50%)

**Arcade Drive Tests:**
- Forward movement (50%, 0)
- Turn right (50%, 25%)
- Turn left (50%, -25%)
- Saturation (80%, 50% → prevents overflow)

**Clamp Tests:**
- Value within range (50 → stays 50)
- Value above max (150 → clamps to 100)
- Value below min (-150 → clamps to -100)

**Deadband Tests:**
- Small input within deadband (3 → returns 0)
- Large input outside deadband (10 → returns 10)
- Negative input within deadband (-3 → returns 0)

---

## 🎓 Key Concepts Explained

### Pure Functions
- **Definition**: Same input always produces same output, no side effects
- **Example**: `clamp(150, -100, 100)` always returns `100`
- **Benefit**: Easy to test, predictable behavior

### AAA Pattern (Arrange-Act-Assert)
- **Arrange**: Set up test data
- **Act**: Execute the code being tested
- **Assert**: Verify the results
- **Benefit**: Clear test structure, easy to understand

### Separation of Concerns
- **Definition**: Separate logic (what to do) from hardware (how to do it)
- **Benefit**: Test logic without hardware, faster development

### Test Independence
- **Definition**: Each test can run alone, doesn't depend on other tests
- **Benefit**: Reliable tests, easy to debug failures

---

## 🚀 How to Use This Project

### 1. Run the Tests
```bash
make test
```
This will:
- Compile the test file and DriveTrain code
- Run all 20 tests
- Show which tests passed/failed
- Output: `✓ All tests passed!`

### 2. Modify the Robot Code
- Edit `main.cpp` to change robot behavior
- Use functions from `DriveTrain.cpp` for drive calculations

### 3. Add New Features Using TDD
1. Write test first (RED phase)
2. Implement feature (GREEN phase)
3. Refactor code (REFACTOR phase)
4. Run tests to verify

### 4. Deploy to Robot
- Use PROS toolchain to compile and upload to VEX V5 Brain
- Test on actual hardware after unit tests pass

---

## 🎯 What You've Learned

1. **TDD Principles**: RED-GREEN-REFACTOR cycle
2. **Testable Architecture**: Separating logic from hardware
3. **Pure Functions**: Making code easy to test
4. **AAA Pattern**: Structuring tests clearly
5. **Best Practices**: Independent tests, edge cases, clear names
6. **Drive Train Control**: Tank drive and arcade drive algorithms

---

## 📝 Summary in One Sentence

**This project demonstrates how to write testable, well-structured robot code by separating drive train logic from hardware, allowing you to test motor control calculations without needing actual motors!**

---

## 🔗 File Relationships

```
main.cpp
  ├─ includes → main.h (VEX library)
  └─ includes → DriveTrain.h
      └─ uses → DriveTrain.cpp functions

test_drivetrain.cpp
  ├─ includes → DriveTrain.h
  └─ tests → DriveTrain.cpp functions

Makefile
  └─ compiles → test_drivetrain.cpp + DriveTrain.cpp
```

---

**Ready to code? Start with `make test` to see everything working!** 🤖✨

