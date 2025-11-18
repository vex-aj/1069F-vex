/*
 * test_intakecontroller.cpp
 * 
 * Unit tests for IntakeController class following TDD principles.
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

// Include our simple test framework
#ifndef SIMPLE_TEST_FRAMEWORK_H
#define SIMPLE_TEST_FRAMEWORK_H

#include <iostream>
#include <string>
#include <cassert>

// Simple test framework for demonstration
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

// Include our IntakeController class to test it
#include "../IntakeController.h"

// ============================================
// TEST CASES FOR INTAKE CONTROLLER
// ============================================

/**
 * Test: Intake Motor - Stop State
 * 
 * Given: Motor state is STOP
 * When: Calculate intake power
 * Then: Should return 0 (motor stopped)
 */
void testIntakePower_Stop() {
    int result = IntakeController::calculateIntakePower(IntakeController::STOP, 50);
    TestRunner::assertEquals(0, result, "Intake Motor - Stop state returns 0");
}

/**
 * Test: Intake Motor - Forward State
 * 
 * Given: Motor state is FORWARD with 50% power
 * When: Calculate intake power
 * Then: Should return 50 (motor forward at 50%)
 */
void testIntakePower_Forward() {
    int result = IntakeController::calculateIntakePower(IntakeController::FORWARD, 50);
    TestRunner::assertEquals(50, result, "Intake Motor - Forward at 50% returns 50");
}

/**
 * Test: Intake Motor - Reverse State
 * 
 * Given: Motor state is REVERSE with 50% power
 * When: Calculate intake power
 * Then: Should return -50 (motor reverse at 50%)
 */
void testIntakePower_Reverse() {
    int result = IntakeController::calculateIntakePower(IntakeController::REVERSE, 50);
    TestRunner::assertEquals(-50, result, "Intake Motor - Reverse at 50% returns -50");
}

/**
 * Test: Intake Motor - Full Power Forward
 * 
 * Given: Motor state is FORWARD with 100% power
 * When: Calculate intake power
 * Then: Should return 100 (full power forward)
 */
void testIntakePower_FullForward() {
    int result = IntakeController::calculateIntakePower(IntakeController::FORWARD, 100);
    TestRunner::assertEquals(100, result, "Intake Motor - Full forward returns 100");
}

/**
 * Test: Ramp Motor - Stop State
 * 
 * Given: Motor state is STOP
 * When: Calculate ramp power
 * Then: Should return 0 (motor stopped)
 */
void testRampPower_Stop() {
    int result = IntakeController::calculateRampPower(IntakeController::STOP, 50);
    TestRunner::assertEquals(0, result, "Ramp Motor - Stop state returns 0");
}

/**
 * Test: Ramp Motor - Forward State
 * 
 * Given: Motor state is FORWARD with 50% power
 * When: Calculate ramp power
 * Then: Should return 50 (motor forward at 50%)
 */
void testRampPower_Forward() {
    int result = IntakeController::calculateRampPower(IntakeController::FORWARD, 50);
    TestRunner::assertEquals(50, result, "Ramp Motor - Forward at 50% returns 50");
}

/**
 * Test: Ramp Motor - Reverse State
 * 
 * Given: Motor state is REVERSE with 50% power
 * When: Calculate ramp power
 * Then: Should return -50 (motor reverse at 50%)
 */
void testRampPower_Reverse() {
    int result = IntakeController::calculateRampPower(IntakeController::REVERSE, 50);
    TestRunner::assertEquals(-50, result, "Ramp Motor - Reverse at 50% returns -50");
}

/**
 * Test: Clamp Power Level - Within Range
 * 
 * Given: Power level 50 (within 0-100)
 * When: Clamp power level
 * Then: Should return 50 (unchanged)
 */
void testClampPowerLevel_WithinRange() {
    int result = IntakeController::clampPowerLevel(50);
    TestRunner::assertEquals(50, result, "Clamp Power - Value within range unchanged");
}

/**
 * Test: Clamp Power Level - Above Maximum
 * 
 * Given: Power level 150 (above 100)
 * When: Clamp power level
 * Then: Should return 100 (clamped to max)
 */
void testClampPowerLevel_AboveMaximum() {
    int result = IntakeController::clampPowerLevel(150);
    TestRunner::assertEquals(100, result, "Clamp Power - Value above max clamped to 100");
}

/**
 * Test: Clamp Power Level - Below Minimum
 * 
 * Given: Power level -50 (below 0)
 * When: Clamp power level
 * Then: Should return 0 (clamped to min)
 */
void testClampPowerLevel_BelowMinimum() {
    int result = IntakeController::clampPowerLevel(-50);
    TestRunner::assertEquals(0, result, "Clamp Power - Value below min clamped to 0");
}

/**
 * Test: Clamp Power Level - At Boundaries
 * 
 * Given: Power level 0 and 100 (at boundaries)
 * When: Clamp power level
 * Then: Should return unchanged (0 and 100)
 */
void testClampPowerLevel_AtBoundaries() {
    int result0 = IntakeController::clampPowerLevel(0);
    int result100 = IntakeController::clampPowerLevel(100);
    TestRunner::assertEquals(0, result0, "Clamp Power - At minimum boundary (0)");
    TestRunner::assertEquals(100, result100, "Clamp Power - At maximum boundary (100)");
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
    std::cout << "=== Running IntakeController Unit Tests ===" << std::endl;
    std::cout << "Following TDD Best Practices\n" << std::endl;
    
    // Run all tests
    testIntakePower_Stop();
    testIntakePower_Forward();
    testIntakePower_Reverse();
    testIntakePower_FullForward();
    testRampPower_Stop();
    testRampPower_Forward();
    testRampPower_Reverse();
    testClampPowerLevel_WithinRange();
    testClampPowerLevel_AboveMaximum();
    testClampPowerLevel_BelowMinimum();
    testClampPowerLevel_AtBoundaries();
    
    // Print results
    TestRunner::printResults();
    
    // Return 0 if all tests passed, 1 if any failed
    return (TestRunner::getFailedCount() > 0) ? 1 : 0;
}

