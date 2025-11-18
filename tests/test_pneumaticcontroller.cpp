/*
 * test_pneumaticcontroller.cpp
 * 
 * Unit tests for PneumaticController class following TDD principles.
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
    
    static void assertEqualsBool(bool expected, bool actual, const std::string& testName) {
        testTotal++;
        if (expected == actual) {
            testsPassed++;
            std::cout << "✓ PASS: " << testName << std::endl;
        } else {
            testsFailed++;
            std::cerr << "✗ FAIL: " << testName 
                      << " (Expected: " << (expected ? "true" : "false") 
                      << ", Got: " << (actual ? "true" : "false") << ")" << std::endl;
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

// Include our PneumaticController class to test it
#include "../src/controllers/PneumaticController.h"

// ============================================
// TEST CASES FOR PNEUMATIC CONTROLLER
// ============================================

/**
 * Test: Piston State - Low Position
 * 
 * Given: Height position is LOW
 * When: Calculate piston state
 * Then: Should return false (pistons retracted)
 */
void testPistonState_Low() {
    bool result = PneumaticController::calculatePistonState(PneumaticController::LOW);
    TestRunner::assertEqualsBool(false, result, "Piston State - LOW position returns false (retracted)");
}

/**
 * Test: Piston State - High Position
 * 
 * Given: Height position is HIGH
 * When: Calculate piston state
 * Then: Should return true (pistons extended)
 */
void testPistonState_High() {
    bool result = PneumaticController::calculatePistonState(PneumaticController::HIGH);
    TestRunner::assertEqualsBool(true, result, "Piston State - HIGH position returns true (extended)");
}

/**
 * Test: Toggle Position - From Low to High
 * 
 * Given: Current position is LOW
 * When: Toggle position
 * Then: Should return HIGH
 */
void testTogglePosition_LowToHigh() {
    PneumaticController::HeightPosition result = PneumaticController::togglePosition(PneumaticController::LOW);
    TestRunner::assertEquals(static_cast<int>(PneumaticController::HIGH), 
                             static_cast<int>(result), 
                             "Toggle Position - LOW to HIGH");
}

/**
 * Test: Toggle Position - From High to Low
 * 
 * Given: Current position is HIGH
 * When: Toggle position
 * Then: Should return LOW
 */
void testTogglePosition_HighToLow() {
    PneumaticController::HeightPosition result = PneumaticController::togglePosition(PneumaticController::HIGH);
    TestRunner::assertEquals(static_cast<int>(PneumaticController::LOW), 
                             static_cast<int>(result), 
                             "Toggle Position - HIGH to LOW");
}

/**
 * Test: Get Opposite Position - From Low
 * 
 * Given: Position is LOW
 * When: Get opposite position
 * Then: Should return HIGH
 */
void testGetOppositePosition_FromLow() {
    PneumaticController::HeightPosition result = PneumaticController::getOppositePosition(PneumaticController::LOW);
    TestRunner::assertEquals(static_cast<int>(PneumaticController::HIGH), 
                             static_cast<int>(result), 
                             "Get Opposite - LOW returns HIGH");
}

/**
 * Test: Get Opposite Position - From High
 * 
 * Given: Position is HIGH
 * When: Get opposite position
 * Then: Should return LOW
 */
void testGetOppositePosition_FromHigh() {
    PneumaticController::HeightPosition result = PneumaticController::getOppositePosition(PneumaticController::HIGH);
    TestRunner::assertEquals(static_cast<int>(PneumaticController::LOW), 
                             static_cast<int>(result), 
                             "Get Opposite - HIGH returns LOW");
}

/**
 * Test: Toggle Twice Returns to Original
 * 
 * Given: Start at LOW position
 * When: Toggle twice
 * Then: Should return to LOW
 */
void testTogglePosition_TwiceReturnsOriginal() {
    PneumaticController::HeightPosition first = PneumaticController::togglePosition(PneumaticController::LOW);
    PneumaticController::HeightPosition second = PneumaticController::togglePosition(first);
    TestRunner::assertEquals(static_cast<int>(PneumaticController::LOW), 
                             static_cast<int>(second), 
                             "Toggle Twice - Returns to original position");
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
    std::cout << "=== Running PneumaticController Unit Tests ===" << std::endl;
    std::cout << "Following TDD Best Practices\n" << std::endl;
    
    // Run all tests
    testPistonState_Low();
    testPistonState_High();
    testTogglePosition_LowToHigh();
    testTogglePosition_HighToLow();
    testGetOppositePosition_FromLow();
    testGetOppositePosition_FromHigh();
    testTogglePosition_TwiceReturnsOriginal();
    
    // Print results
    TestRunner::printResults();
    
    // Return 0 if all tests passed, 1 if any failed
    return (TestRunner::getFailedCount() > 0) ? 1 : 0;
}

