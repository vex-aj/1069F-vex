/*
 * IntakeController.cpp
 * 
 * Implementation of intake and ramp motor control logic.
 * These are pure functions - no hardware dependencies, fully testable!
 */

#include "IntakeController.h"

int IntakeController::calculateIntakePower(MotorState state, int powerLevel) {
    // If motor should stop, return 0 regardless of power level
    if (state == STOP) {
        return 0;
    }
    
    // Clamp power level to valid range (0-100)
    int clampedPower = clampPowerLevel(powerLevel);
    
    // Return positive power for forward, negative for reverse
    if (state == FORWARD) {
        return clampedPower;
    } else if (state == REVERSE) {
        return -clampedPower;
    }
    
    // Default to stop (shouldn't reach here, but safety check)
    return 0;
}

int IntakeController::calculateRampPower(MotorState state, int powerLevel) {
    // Ramp motor uses same logic as intake motor
    // If motor should stop, return 0 regardless of power level
    if (state == STOP) {
        return 0;
    }
    
    // Clamp power level to valid range (0-100)
    int clampedPower = clampPowerLevel(powerLevel);
    
    // Return positive power for forward, negative for reverse
    if (state == FORWARD) {
        return clampedPower;
    } else if (state == REVERSE) {
        return -clampedPower;
    }
    
    // Default to stop (shouldn't reach here, but safety check)
    return 0;
}

int IntakeController::clampPowerLevel(int powerLevel) {
    // Ensure power level stays within 0-100 range
    if (powerLevel < 0) {
        return 0;
    }
    if (powerLevel > 100) {
        return 100;
    }
    return powerLevel;
}

