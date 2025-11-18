/*
 * RampController.cpp
 * 
 * Implementation of full power ramp motor control logic.
 * This is for the final ramp wheel that pushes balls out at the top.
 * These are pure functions - no hardware dependencies, fully testable!
 */

#include "RampController.h"

int RampController::calculateRampPower(MotorState state, bool useFullPower, int powerLevel) {
    // If motor should stop, return 0 regardless of power mode or level
    if (state == STOP) {
        return 0;
    }
    
    // If using full power mode, return 100% (or -100% for reverse)
    if (useFullPower) {
        if (state == FORWARD) {
            return 100;
        } else if (state == REVERSE) {
            return -100;
        }
    }
    
    // Variable power mode: use the provided power level
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

int RampController::clampPowerLevel(int powerLevel) {
    // Ensure power level stays within 0-100 range
    if (powerLevel < 0) {
        return 0;
    }
    if (powerLevel > 100) {
        return 100;
    }
    return powerLevel;
}

