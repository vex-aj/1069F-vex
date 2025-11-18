## C++ Code Style Guidelines for VEX V5 Robotics

### Standards & Framework
* **C++ Standard**: C++17 (required for PROS framework)
* **Framework**: PROS (Professional Robotics Operating System) for VEX V5
* **Build System**: PROS toolchain (`pros make`, `pros upload`) or Makefile for local testing
* **Includes**: Order: system includes, VEX includes (`vex.h`), local includes (blank line between groups)
* **Namespaces**: Use `vex` namespace for all VEX classes; `using namespace vex;` in .cpp files

### Code Organization & Architecture
* **Separation of Concerns**: Always separate testable logic from hardware dependencies
  * Hardware layer (`main.cpp`): Motor declarations, controller, brain, competition
  * Logic layer (e.g., `DriveTrain.cpp`): Pure functions, calculations, algorithms (testable!)
  * Test layer (`tests/`): Unit tests for logic layer
* **Headers**: Use header guards (`#ifndef CLASSNAME_H`), forward declarations preferred in headers
* **File Structure**: 
  * `main.cpp` / `main.h` - Hardware integration and robot control
  * Separate classes for testable logic (e.g., `DriveTrain.h` / `DriveTrain.cpp`)
  * `tests/` directory for all unit tests

### Naming Conventions
* **Classes**: CamelCase (e.g., `DriveTrain`, `MotorController`)
* **Methods**: camelCase (e.g., `calculateTankDrive()`, `applyDeadband()`, `clamp()`)
* **Variables**: 
  * Global/static: CamelCase (e.g., `LeftFrontMotor`, `Controller1`)
  * Local: camelCase (e.g., `leftStickInput`, `rightPower`)
* **Constants**: UPPER_SNAKE_CASE (e.g., `MAX_MOTOR_POWER`, `DEADBAND_THRESHOLD`)
* **No Prefixes**: Do NOT use `p_` for parameters or `m_` for members (use descriptive names instead)

### PROS-Specific Patterns
* **Motor Declarations**: `motor MotorName = motor(PORT#, ratio##_1, reversed);`
  * Use descriptive names indicating position/function (e.g., `LeftFrontMotor`, `IntakeMotor`)
  * Gear ratios: `ratio36_1` (red), `ratio18_1` (green), `ratio6_1` (blue), or `green`/`red`/`blue`
  * Reversal: `true`/`false` - adjust based on physical robot orientation
* **Motor Groups**: Use `motor_group` to control multiple motors together
* **Controller**: `controller Controller1 = controller(primary);`
* **Competition**: `competition Competition;` - Required for competition mode
* **Brain**: `brain Brain;` - Required global declaration
* **Functions**: 
  * `autonomous()` - Runs during autonomous period
  * `usercontrol()` - Runs during driver control period
  * `vexcodeInit()` - Initialization function

### Test-Driven Development (TDD) Requirements
* **RED-GREEN-REFACTOR Cycle**: Always follow TDD workflow
  1. **RED**: Write test first (it will fail - this is expected!)
  2. **GREEN**: Write minimal code to make test pass
  3. **REFACTOR**: Improve code while keeping tests passing
* **Incremental Development**: Break all work into small, testable chunks
  * Each feature/function must have passing tests before moving to the next chunk
  * Never add multiple features without tests between them
  * Run `make test` frequently (after each small change)
* **Test Requirements**:
  * All logic functions must have unit tests
  * Tests must be independent (can run in any order)
  * Use AAA pattern (Arrange-Act-Assert) in tests
  * Test edge cases (boundary conditions, overflow, zero values)
  * Test pure functions without hardware dependencies
* **Test Location**: All tests in `tests/` directory
* **Test Naming**: `test[Function]_[Scenario]_[ExpectedResult]()` (e.g., `testClamp_AboveMaximum()`)

### Code Documentation & Explanation
* **Explain Everything**: All code must be clearly explained
  * **Function comments**: Use `/** */` style with `@param` and `@return` tags
  * **Inline comments**: Explain WHY, not just WHAT (especially for complex logic)
  * **Complex calculations**: Break down formulas with comments
  * **Hardware setup**: Comment motor ports, gear ratios, and why reversal flags are set
* **Comment Examples**:
  ```cpp
  /**
   * Calculate tank drive motor powers
   * 
   * Pure function: same input always produces same output (easy to test!)
   * 
   * @param leftStickInput Input from left stick (-100 to 100)
   * @param rightStickInput Input from right stick (-100 to 100)
   * @param leftPower Output parameter for left motor power (-100 to 100)
   * @param rightPower Output parameter for right motor power (-100 to 100)
   */
  ```
* **Code Clarity**: 
  - Use descriptive variable names (avoid abbreviations unless standard)
  - Break complex operations into multiple lines with comments
  - Explain non-obvious decisions (e.g., why a motor is reversed)

### Memory & Resource Management
* **No Dynamic Allocation**: Avoid `new`/`delete` in robot code (use stack allocation)
* **Static Functions**: Prefer static methods for pure logic functions (e.g., `DriveTrain::calculateTankDrive()`)
* **Global Objects**: VEX objects (motors, controller, brain) are declared globally
* **Motor Groups**: Use `motor_group` to manage multiple motors efficiently

### Error Handling
* **Input Validation**: Clamp values to valid ranges (e.g., -100 to 100 for motor power)
* **Deadband**: Always apply deadband to controller input to prevent drift
* **Bounds Checking**: Check array bounds, port numbers, and sensor values
* **Comments for Edge Cases**: Document what happens at boundaries

### Formatting
* **Indentation**: 2 spaces (not tabs)
* **Line Length**: 100 characters maximum
* **Pointer/Reference Alignment**: Right-aligned (e.g., `int& leftPower`, `motor* motorPtr`)
* **Braces**: Opening brace on same line for functions/classes, new line for control structures
* **Spacing**: 
  - Blank line between function definitions
  - Blank line between logical sections within functions
  - Space after commas, around operators

### Workflow Requirements
* **Small Chunks**: Break all work into small, focused changes
  * One function/feature at a time
  * Each chunk must have passing tests before moving on
  * Commit frequently with clear messages
* **Test First**: Always write tests before implementation
* **Run Tests**: Execute `make test` after every change
* **Explain Changes**: Commit messages should explain what and why
* **Review Before Commit**: Ensure all tests pass and code is explained

### Example Code Structure
```cpp
// main.cpp - Hardware layer
#include "main.h"
#include "DriveTrain.h"

using namespace vex;

brain Brain;
motor LeftMotor = motor(PORT1, ratio18_1, false);
motor RightMotor = motor(PORT2, ratio18_1, true);
controller Controller1 = controller(primary);
competition Competition;

void usercontrol(void) {
    while (true) {
        // Read controller input
        int leftInput = Controller1.Axis3.position();
        int rightInput = Controller1.Axis2.position();
        
        // Apply deadband to prevent drift
        leftInput = DriveTrain::applyDeadband(leftInput, 5);
        rightInput = DriveTrain::applyDeadband(rightInput, 5);
        
        // Calculate motor powers (testable logic!)
        int leftPower, rightPower;
        DriveTrain::calculateTankDrive(leftInput, rightInput, leftPower, rightPower);
        
        // Set motor speeds
        LeftMotor.spin(forward, leftPower, percent);
        RightMotor.spin(forward, rightPower, percent);
        
        wait(20, msec);
    }
}
```

```cpp
// DriveTrain.h - Logic layer (testable)
#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

class DriveTrain {
public:
    static void calculateTankDrive(int leftStickInput, int rightStickInput, 
                                   int& leftPower, int& rightPower);
    static int clamp(int value, int min, int max);
    static int applyDeadband(int input, int deadband);
};

#endif // DRIVETRAIN_H
```
