# Test-Driven Development (TDD) Guide for VEX V5 Robotics

## What is TDD?

Test-Driven Development is a development methodology where you:
1. **RED**: Write a test first (it will fail because code doesn't exist)
2. **GREEN**: Write minimal code to make the test pass
3. **REFACTOR**: Improve the code while keeping tests passing

Repeat this cycle for each new feature!

## Why TDD for Robotics?

### Benefits:
- ✅ **Catch bugs early**: Find problems before hardware testing
- ✅ **Confidence in changes**: Refactor safely knowing tests will catch breaks
- ✅ **Better design**: Forces you to write testable, modular code
- ✅ **Documentation**: Tests show how code is supposed to work
- ✅ **Faster development**: Test pure logic quickly without hardware

### Challenges with Robotics:
- ⚠️ **Hardware dependencies**: Motors, sensors, etc. are hard to test
- ⚠️ **Real-time constraints**: Some code must run on hardware
- ⚠️ **Integration testing**: Need to test with actual robot

## Solution: Separate Logic from Hardware

### The Key Principle:
**Separate pure logic (testable) from hardware control (needs hardware testing)**

```
BAD (Hard to Test):
┌─────────────────────┐
│  main.cpp           │
│  - Motors           │  ← Hardware mixed with logic
│  - Drive logic      │
│  - Controller input │
└─────────────────────┘

GOOD (Testable):
┌─────────────────────┐     ┌─────────────────────┐
│  DriveTrain.cpp     │     │  main.cpp           │
│  - Pure functions   │ ←── │  - Hardware         │
│  - Testable logic   │     │  - Calls DriveTrain │
└─────────────────────┘     └─────────────────────┘
         ↑
         │ Easy to test!
┌─────────────────────┐
│  test_drivetrain.cpp│
│  - Unit tests       │
└─────────────────────┘
```

## Best Practices for C++ Testing in Robotics

### 1. **Use Descriptive Test Names**
```cpp
// BAD: Unclear what this tests
void test1() { ... }

// GOOD: Clear what behavior is being tested
void testArcadeDrive_TurnRight() { ... }
void testClamp_AboveMaximum() { ... }
```

**Follow the pattern**: `test[Function]_[Scenario]_[ExpectedResult]`

### 2. **Write Independent Tests**
Each test should:
- Be able to run alone
- Not depend on other tests
- Not share state with other tests
- Be able to run in any order

```cpp
// BAD: Depends on previous test
void test2() {
    int value = globalVariable;  // ← Assumes test1 ran first
}

// GOOD: Self-contained
void testClamp_AboveMaximum() {
    int result = DriveTrain::clamp(150, -100, 100);
    // No dependencies on other tests
}
```

### 3. **Test Edge Cases**
Don't just test the "happy path" - test boundaries!

```cpp
// Test normal cases
testArcadeDrive_Forward();

// Test edge cases
testArcadeDrive_Saturation();        // ← What if result > 100?
testClamp_BelowMinimum();            // ← What if input < -100?
testDeadband_WithinThreshold();      // ← What if input is tiny?
```

Common edge cases for robotics:
- **Boundary values**: -100, 0, 100 (motor limits)
- **Overflow**: Values that exceed limits
- **Zero/empty**: No input, zero power
- **Negative values**: Reverse direction

### 4. **Keep Tests Fast**
- Use pure functions (no hardware I/O)
- Avoid delays or waiting
- Run entire test suite in seconds

```cpp
// BAD: Slow (waits for hardware)
void testMotor() {
    motor.spin(forward, 50, percent);
    wait(1000, msec);  // ← Too slow!
}

// GOOD: Fast (pure logic)
void testArcadeDrive() {
    int left, right;
    DriveTrain::calculateArcadeDrive(50, 0, left, right);
    // ← Instant, no hardware needed
}
```

### 5. **Test One Thing at a Time**
Each test should verify one specific behavior:

```cpp
// BAD: Tests multiple things
void testDriveTrain() {
    // Tests tank drive
    // Tests arcade drive
    // Tests clamping
    // ← Too much! Hard to find what failed
}

// GOOD: One test, one behavior
void testTankDrive_Forward() { ... }
void testArcadeDrive_TurnRight() { ... }
void testClamp_AboveMaximum() { ... }
```

### 6. **Use AAA Pattern**
Structure tests clearly using the **AAA Pattern**:

#### What is AAA Pattern?

AAA stands for **Arrange, Act, Assert** - a way to structure your tests into three distinct sections:

1. **ARRANGE** (Given): Set up all the test data and inputs needed for your test
2. **ACT** (When): Execute the code you're testing (call the function/method)
3. **ASSERT** (Then): Verify that the results are correct (check the outputs)

This pattern makes tests:
- ✅ **Readable**: Easy to understand what's being tested
- ✅ **Maintainable**: Clear structure helps when debugging
- ✅ **Standard**: Consistent format across all tests

#### Example:

```cpp
void testArcadeDrive_TurnRight() {
    // ===== ARRANGE (Given) =====
    // Set up all test data and inputs
    int forwardInput = 50;    // Forward stick at 50%
    int turnInput = 25;       // Turn stick at 25% (right)
    int leftPower, rightPower; // Variables to hold results
    
    // ===== ACT (When) =====
    // Execute the code being tested
    DriveTrain::calculateArcadeDrive(forwardInput, turnInput, 
                                     leftPower, rightPower);
    
    // ===== ASSERT (Then) =====
    // Verify the results are correct
    TestRunner::assertEquals(75, leftPower, "Left motor faster (50 + 25)");
    TestRunner::assertEquals(25, rightPower, "Right motor slower (50 - 25)");
}
```

#### Real-World Example from Our Tests:

```cpp
void testClamp_AboveMaximum() {
    // ARRANGE: Set up the test scenario
    int value = 150;      // Value exceeds maximum
    int min = -100;       // Minimum allowed
    int max = 100;        // Maximum allowed
    
    // ACT: Execute the clamp function
    int result = DriveTrain::clamp(value, min, max);
    
    // ASSERT: Verify it was clamped correctly
    TestRunner::assertEquals(100, result, "Value above max clamped to max");
}
```

#### Why This Matters:

**Without AAA Pattern** (harder to read):
```cpp
void testSomething() {
    int result = DriveTrain::clamp(DriveTrain::calculateArcadeDrive(50, 25, left, right), -100, 100);
    assert(result == 100); // What's being tested? What's the expected behavior?
}
```

**With AAA Pattern** (clear and readable):
```cpp
void testSomething() {
    // ARRANGE: I can see the test setup
    int input = 150;
    
    // ACT: I can see what function is being tested
    int result = DriveTrain::clamp(input, -100, 100);
    
    // ASSERT: I can see what the expected result is
    TestRunner::assertEquals(100, result, "Clamps to max");
}
```

#### The Three As Explained:

**Arrange (Given):**
- Create variables and set their values
- Initialize objects needed for the test
- Set up any preconditions
- Answer: "What are the starting conditions?"

**Act (When):**
- Call the function or method being tested
- Execute the code that produces the result
- Answer: "What action are we testing?"

**Assert (Then):**
- Check that the results match expectations
- Verify all outputs are correct
- Answer: "What should the result be?"

## Testing Frameworks for C++

### What We Actually Used: Simple Custom Framework ✅

**This project uses a simple custom test framework** (found in `tests/test_drivetrain.cpp`). This is great for learning because:
- ✅ **Zero dependencies** - No external libraries needed
- ✅ **Full control** - You see exactly how testing works
- ✅ **Good for learning** - Understand the fundamentals first
- ⚠️ **Limited features** - Basic assertions only (no mocking, etc.)

This framework includes:
- `TestRunner::assertEquals()` - Compare expected vs actual values
- `TestRunner::assertTrue()` - Check boolean conditions
- `TestRunner::printResults()` - Display test summary

### Other Framework Options (For Real Projects)

#### Option 1: Catch2 (Recommended for Production Embedded)
- ✅ Header-only (easy to include)
- ✅ Simple syntax
- ✅ Works well with embedded systems
- ✅ Active development
- ✅ Great features (mocking, fixtures, etc.)

**Installation**: Download single header file from GitHub

#### Option 2: Google Test (gtest)
- ✅ Very popular and mature
- ✅ Extensive features
- ⚠️ Requires linking library
- ✅ Great documentation

#### Option 3: Simple Custom Framework (What We Used)
- ✅ Zero dependencies
- ✅ Full control
- ⚠️ Limited features
- ✅ Good for learning (used in our example)

## TDD Workflow Example

Let's say you want to add a "ramp rate" feature (gradual acceleration):

### Step 1: RED - Write the Test First
```cpp
void testRampRate_GradualIncrease() {
    // Test that power ramps from 0 to 100 gradually
    int currentPower = 0;
    int targetPower = 100;
    int rampRate = 10;
    
    int result = DriveTrain::applyRampRate(currentPower, targetPower, rampRate);
    
    TestRunner::assertEquals(10, result, "First ramp step");
}
```

**Run the test** → It fails (function doesn't exist yet) ✓ This is expected!

### Step 2: GREEN - Write Minimal Code
```cpp
int DriveTrain::applyRampRate(int current, int target, int rate) {
    if (target > current) {
        return current + rate;  // Minimal code to pass test
    }
    return current;
}
```

**Run the test** → It passes! ✓

### Step 3: REFACTOR - Improve Code
```cpp
int DriveTrain::applyRampRate(int current, int target, int rate) {
    int difference = target - current;
    
    if (abs(difference) <= rate) {
        return target;  // Close enough, just return target
    }
    
    return (target > current) ? current + rate : current - rate;
}
```

**Run ALL tests** → Still passing! ✓ Safe to refactor

### Step 4: Add More Tests
Now write tests for edge cases:
- Ramp down (target < current)
- Target already reached
- Large ramp rates

## Running Tests

### Compile and Run Tests
```bash
# Compile test file (if using our simple framework)
g++ -std=c++17 tests/test_drivetrain.cpp -o test_runner

# Run tests
./test_runner
```

### In Your IDE
Set up a test configuration to run tests with one click!

## Integration Testing

Unit tests verify logic, but you also need:

### Hardware-in-the-Loop Testing
- Test on actual robot
- Verify motors respond correctly
- Check sensor readings
- Validate autonomous routines

### Manual Testing Checklist
- [ ] Motors spin in correct direction
- [ ] Controller input maps correctly
- [ ] Deadband prevents drift
- [ ] Autonomous routine executes properly

## Common Pitfalls to Avoid

### ❌ Don't Test Implementation Details
```cpp
// BAD: Tests internal variable
void test() {
    assert(drivetrain.internalCounter == 5);  // ← Too specific!
}
```

### ✅ Test Public Behavior
```cpp
// GOOD: Tests what the function does
void testArcadeDrive_TurnRight() {
    // Tests the output, not how it's calculated
}
```

### ❌ Don't Write Tests That Require Specific Execution Order
```cpp
// BAD: Assumes previous test set up state
void test2() {
    useStateFromTest1();  // ← Fragile!
}
```

### ✅ Make Tests Independent
```cpp
// GOOD: Each test sets up its own state
void test2() {
    DriveTrain drivetrain;  // ← Fresh state
    // Test...
}
```

## Summary

1. **Write tests first** (RED phase)
2. **Make them pass** (GREEN phase)
3. **Improve code** (REFACTOR phase)
4. **Separate logic from hardware** for testability
5. **Test edge cases** not just happy paths
6. **Keep tests fast and independent**

## Next Steps

1. Run the example tests: `g++ -std=c++17 tests/test_drivetrain.cpp -o test_runner && ./test_runner`
2. Write a new test for a feature you want to add
3. Implement the feature to make the test pass
4. Refactor and improve
5. Repeat!

Happy testing! 🤖🧪

