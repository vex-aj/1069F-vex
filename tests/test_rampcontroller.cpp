/*
 * test_rampcontroller.cpp
 * 
 * Unit tests for RampController class following TDD principles.
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

// Include our RampController class to test it
#include "../src/controllers/RampController.h"

// ============================================
// TEST CASES FOR RAMP CONTROLLER
// ============================================

/**
 * Test: Full Power Ramp Motor - Stop State
 * 
 * Given: Motor state is STOP
 * When: Calculate ramp power
 * Then: Should return 0 (motor stopped) regardless of power mode
 */
void testRampPower_Stop() {
    int resultFull = RampController::calculateRampPower(RampController::STOP, true, 50);
    int resultVar = RampController::calculateRampPower(RampController::STOP, false, 50);
    
    TestRunner::assertEquals(0, resultFull, "Ramp Motor - Stop state with full power mode returns 0");
    TestRunner::assertEquals(0, resultVar, "Ramp Motor - Stop state with variable power mode returns 0");
}

/**
 * Test: Full Power Ramp Motor - Forward with Full Power
 * 
 * Given: Motor state is FORWARD, useFullPower is true
 * When: Calculate ramp power
 * Then: Should return 100 (full power forward)
 */
void testRampPower_ForwardFullPower() {
    int result = RampController::calculateRampPower(RampController::FORWARD, true, 50);
    TestRunner::assertEquals(100, result, "Ramp Motor - Forward with full power returns 100");
}

/**
 * Test: Full Power Ramp Motor - Reverse with Full Power
 * 
 * Given: Motor state is REVERSE, useFullPower is true
 * When: Calculate ramp power
 * Then: Should return -100 (full power reverse)
 */
void testRampPower_ReverseFullPower() {
    int result = RampController::calculateRampPower(RampController::REVERSE, true, 50);
    TestRunner::assertEquals(-100, result, "Ramp Motor - Reverse with full power returns -100");
}

/**
 * Test: Full Power Ramp Motor - Forward with Variable Power
 * 
 * Given: Motor state is FORWARD, useFullPower is false, powerLevel is 75
 * When: Calculate ramp power
 * Then: Should return 75 (variable power forward)
 */
void testRampPower_ForwardVariablePower() {
    int result = RampController::calculateRampPower(RampController::FORWARD, false, 75);
    TestRunner::assertEquals(75, result, "Ramp Motor - Forward with variable power (75%) returns 75");
}

/**
 * Test: Full Power Ramp Motor - Reverse with Variable Power
 * 
 * Given: Motor state is REVERSE, useFullPower is false, powerLevel is 75
 * When: Calculate ramp power
 * Then: Should return -75 (variable power reverse)
 */
void testRampPower_ReverseVariablePower() {
    int result = RampController::calculateRampPower(RampController::REVERSE, false, 75);
    TestRunner::assertEquals(-75, result, "Ramp Motor - Reverse with variable power (75%) returns -75");
}

/**
 * Test: Full Power Ramp Motor - Variable Power at 50%
 * 
 * Given: Motor state is FORWARD, useFullPower is false, powerLevel is 50
 * When: Calculate ramp power
 * Then: Should return 50
 */
void testRampPower_VariablePower50() {
    int result = RampController::calculateRampPower(RampController::FORWARD, false, 50);
    TestRunner::assertEquals(50, result, "Ramp Motor - Variable power at 50% returns 50");
}

/**
 * Test: Clamp Power Level - Within Range
 * 
 * Given: Power level 50 (within 0-100)
 * When: Clamp power level
 * Then: Should return 50 (unchanged)
 */
void testClampPowerLevel_WithinRange() {
    int result = RampController::clampPowerLevel(50);
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
    int result = RampController::clampPowerLevel(150);
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
    int result = RampController::clampPowerLevel(-50);
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
    int result0 = RampController::clampPowerLevel(0);
    int result100 = RampController::clampPowerLevel(100);
    TestRunner::assertEquals(0, result0, "Clamp Power - At minimum boundary (0)");
    TestRunner::assertEquals(100, result100, "Clamp Power - At maximum boundary (100)");
}

/**
 * Test: Full Power Mode Ignores Power Level
 * 
 * Given: Motor state is FORWARD, useFullPower is true, powerLevel is 50
 * When: Calculate ramp power
 * Then: Should return 100 (full power, ignoring powerLevel parameter)
 */
void testRampPower_FullPowerIgnoresLevel() {
    int result = RampController::calculateRampPower(RampController::FORWARD, true, 50);
    TestRunner::assertEquals(100, result, "Ramp Motor - Full power mode ignores power level parameter");
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
    std::cout << "=== Running RampController Unit Tests ===" << std::endl;
    std::cout << "Following TDD Best Practices\n" << std::endl;
    
    // Run all tests
    testRampPower_Stop();
    testRampPower_ForwardFullPower();
    testRampPower_ReverseFullPower();
    testRampPower_ForwardVariablePower();
    testRampPower_ReverseVariablePower();
    testRampPower_VariablePower50();
    testClampPowerLevel_WithinRange();
    testClampPowerLevel_AboveMaximum();
    testClampPowerLevel_BelowMinimum();
    testClampPowerLevel_AtBoundaries();
    testRampPower_FullPowerIgnoresLevel();
    
    // Print results
    TestRunner::printResults();
    
    // Return 0 if all tests passed, 1 if any failed
    return (TestRunner::getFailedCount() > 0) ? 1 : 0;
}

