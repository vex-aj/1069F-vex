/*
 * test_drivetrain.cpp
 * 
 * Unit tests for DriveTrain class following TDD principles.
 * 
 * TDD RED-GREEN-REFACTOR CYCLE:
 * 1. RED: Write a test that fails (functionality doesn't exist yet)
 * 2. GREEN: Write minimal code to make the test pass
 * 3. REFACTOR: Improve code quality while keeping tests passing
 * 
 * Best Practices Followed:
 * - Tests are independent (can run in any order)
 * - Tests are fast (pure functions, no hardware)
 * - Tests are descriptive (clear names explain what they test)
 * - Tests cover edge cases (boundary conditions)
 */

// For embedded/robotics testing, we'll use a simple test framework
// In production, you'd use Catch2 or Google Test
// This is a minimal example framework for demonstration

#ifndef SIMPLE_TEST_FRAMEWORK_H
#define SIMPLE_TEST_FRAMEWORK_H

#include <iostream>
#include <string>
#include <cassert>

// Simple test framework for demonstration
// In real projects, use Catch2 or Google Test
class TestRunner {
private:
    static int testsPassed;
    static int testsFailed;
    static int testTotal;
    
public:
    static void assertEquals(int expected, int actual, const std::string& testName) {
        testTotal++;
        if (expected == actual) {
            testsPassed++;
            std::cout << "✓ PASS: " << testName << std::endl;
        } else {
            testsFailed++;
            std::cerr << "✗ FAIL: " << testName 
                      << " (Expected: " << expected << ", Got: " << actual << ")" << std::endl;
        }
    }
    
    static void assertTrue(bool condition, const std::string& testName) {
        testTotal++;
        if (condition) {
            testsPassed++;
            std::cout << "✓ PASS: " << testName << std::endl;
        } else {
            testsFailed++;
            std::cerr << "✗ FAIL: " << testName << std::endl;
        }
    }
    
    static void printResults() {
        std::cout << "\n=== Test Results ===" << std::endl;
        std::cout << "Total: " << testTotal << std::endl;
        std::cout << "Passed: " << testsPassed << std::endl;
        std::cout << "Failed: " << testsFailed << std::endl;
        
        if (testsFailed == 0) {
            std::cout << "✓ All tests passed!" << std::endl;
        } else {
            std::cout << "✗ Some tests failed!" << std::endl;
        }
    }
    
    static int getFailedCount() {
        return testsFailed;
    }
};

int TestRunner::testsPassed = 0;
int TestRunner::testsFailed = 0;
int TestRunner::testTotal = 0;

#endif // SIMPLE_TEST_FRAMEWORK_H

// Include our DriveTrain class to test it
// Note: In a real embedded environment, we might need to mock VEX dependencies
#include "../DriveTrain.h"

// ============================================
// TEST CASES FOR DRIVE TRAIN
// ============================================

/**
 * Test: Tank Drive - Basic Forward Movement
 * 
 * Given: Left stick at 50%, right stick at 50%
 * When: Calculate tank drive powers
 * Then: Both motors should be set to 50%
 */
void testTankDrive_Forward() {
    int leftPower, rightPower;
    DriveTrain::calculateTankDrive(50, 50, leftPower, rightPower);
    
    TestRunner::assertEquals(50, leftPower, "Tank Drive - Left motor forward at 50%");
    TestRunner::assertEquals(50, rightPower, "Tank Drive - Right motor forward at 50%");
}

/**
 * Test: Tank Drive - Reverse Movement
 * 
 * Given: Left stick at -50%, right stick at -50%
 * When: Calculate tank drive powers
 * Then: Both motors should be set to -50%
 */
void testTankDrive_Reverse() {
    int leftPower, rightPower;
    DriveTrain::calculateTankDrive(-50, -50, leftPower, rightPower);
    
    TestRunner::assertEquals(-50, leftPower, "Tank Drive - Left motor reverse at -50%");
    TestRunner::assertEquals(-50, rightPower, "Tank Drive - Right motor reverse at -50%");
}

/**
 * Test: Tank Drive - Turning Left
 * 
 * Given: Left stick at -50%, right stick at 50%
 * When: Calculate tank drive powers
 * Then: Left motor should reverse, right motor should go forward (spin in place)
 */
void testTankDrive_TurnLeft() {
    int leftPower, rightPower;
    DriveTrain::calculateTankDrive(-50, 50, leftPower, rightPower);
    
    TestRunner::assertEquals(-50, leftPower, "Tank Drive - Turn left, left motor reverse");
    TestRunner::assertEquals(50, rightPower, "Tank Drive - Turn left, right motor forward");
}

/**
 * Test: Clamp - Values Within Range
 * 
 * Given: A value that's already within the valid range
 * When: Clamp the value
 * Then: The value should remain unchanged
 */
void testClamp_WithinRange() {
    int result = DriveTrain::clamp(50, -100, 100);
    TestRunner::assertEquals(50, result, "Clamp - Value within range unchanged");
}

/**
 * Test: Clamp - Values Above Maximum
 * 
 * Given: A value above the maximum allowed
 * When: Clamp the value
 * Then: The value should be capped at maximum
 */
void testClamp_AboveMaximum() {
    int result = DriveTrain::clamp(150, -100, 100);
    TestRunner::assertEquals(100, result, "Clamp - Value above max clamped to max");
}

/**
 * Test: Clamp - Values Below Minimum
 * 
 * Given: A value below the minimum allowed
 * When: Clamp the value
 * Then: The value should be capped at minimum
 */
void testClamp_BelowMinimum() {
    int result = DriveTrain::clamp(-150, -100, 100);
    TestRunner::assertEquals(-100, result, "Clamp - Value below min clamped to min");
}

/**
 * Test: Arcade Drive - Forward Movement
 * 
 * Given: Forward input 50%, no turn
 * When: Calculate arcade drive powers
 * Then: Both motors should be at 50%
 */
void testArcadeDrive_Forward() {
    int leftPower, rightPower;
    DriveTrain::calculateArcadeDrive(50, 0, leftPower, rightPower);
    
    TestRunner::assertEquals(50, leftPower, "Arcade Drive - Forward, left motor");
    TestRunner::assertEquals(50, rightPower, "Arcade Drive - Forward, right motor");
}

/**
 * Test: Arcade Drive - Turn Right
 * 
 * Given: Forward input 50%, turn input 25%
 * When: Calculate arcade drive powers
 * Then: Left motor should be 75% (50+25), right motor should be 25% (50-25)
 */
void testArcadeDrive_TurnRight() {
    int leftPower, rightPower;
    DriveTrain::calculateArcadeDrive(50, 25, leftPower, rightPower);
    
    TestRunner::assertEquals(75, leftPower, "Arcade Drive - Turn right, left motor faster");
    TestRunner::assertEquals(25, rightPower, "Arcade Drive - Turn right, right motor slower");
}

/**
 * Test: Arcade Drive - Turn Left
 * 
 * Given: Forward input 50%, turn input -25%
 * When: Calculate arcade drive powers
 * Then: Left motor should be 25% (50+(-25)), right motor should be 75% (50-(-25))
 */
void testArcadeDrive_TurnLeft() {
    int leftPower, rightPower;
    DriveTrain::calculateArcadeDrive(50, -25, leftPower, rightPower);
    
    TestRunner::assertEquals(25, leftPower, "Arcade Drive - Turn left, left motor slower");
    TestRunner::assertEquals(75, rightPower, "Arcade Drive - Turn left, right motor faster");
}

/**
 * Test: Arcade Drive - Saturation (Prevent Overflow)
 * 
 * Given: Forward input 80%, turn input 50%
 * When: Calculate arcade drive powers
 * Then: Left motor should clamp to 100% (not 130%), right motor should be 30%
 */
void testArcadeDrive_Saturation() {
    int leftPower, rightPower;
    DriveTrain::calculateArcadeDrive(80, 50, leftPower, rightPower);
    
    TestRunner::assertEquals(100, leftPower, "Arcade Drive - Left motor saturates at 100%");
    TestRunner::assertEquals(30, rightPower, "Arcade Drive - Right motor doesn't saturate");
}

/**
 * Test: Deadband - Input Within Deadband
 * 
 * Given: Controller input of 3 with deadband of 5
 * When: Apply deadband
 * Then: Should return 0 (prevent drift)
 */
void testDeadband_WithinThreshold() {
    int result = DriveTrain::applyDeadband(3, 5);
    TestRunner::assertEquals(0, result, "Deadband - Small input returns 0");
}

/**
 * Test: Deadband - Input Outside Deadband
 * 
 * Given: Controller input of 10 with deadband of 5
 * When: Apply deadband
 * Then: Should return original value (10)
 */
void testDeadband_OutsideThreshold() {
    int result = DriveTrain::applyDeadband(10, 5);
    TestRunner::assertEquals(10, result, "Deadband - Large input unchanged");
}

/**
 * Test: Deadband - Negative Input
 * 
 * Given: Controller input of -3 with deadband of 5
 * When: Apply deadband
 * Then: Should return 0 (within deadband)
 */
void testDeadband_NegativeInput() {
    int result = DriveTrain::applyDeadband(-3, 5);
    TestRunner::assertEquals(0, result, "Deadband - Small negative input returns 0");
}

// ============================================
// MAIN TEST RUNNER
// ============================================

/**
 * Run all tests
 * 
 * In TDD: This is where you run your test suite frequently
 * - After writing new code (to ensure it works)
 * - Before refactoring (to ensure you don't break anything)
 * - During development (continuous feedback)
 */
int main() {
    std::cout << "=== Running DriveTrain Unit Tests ===" << std::endl;
    std::cout << "Following TDD Best Practices\n" << std::endl;
    
    // Run all tests
    testTankDrive_Forward();
    testTankDrive_Reverse();
    testTankDrive_TurnLeft();
    testClamp_WithinRange();
    testClamp_AboveMaximum();
    testClamp_BelowMinimum();
    testArcadeDrive_Forward();
    testArcadeDrive_TurnRight();
    testArcadeDrive_TurnLeft();
    testArcadeDrive_Saturation();
    testDeadband_WithinThreshold();
    testDeadband_OutsideThreshold();
    testDeadband_NegativeInput();
    
    // Print results
    TestRunner::printResults();
    
    // Return 0 if all tests passed, 1 if any failed
    return (TestRunner::getFailedCount() > 0) ? 1 : 0;
}

