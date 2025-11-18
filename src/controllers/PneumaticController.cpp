/*
 * PneumaticController.cpp
 * 
 * Implementation of pneumatic piston control logic.
 * Two pistons work together to adjust the height of the full power ramp wheel.
 * These are pure functions - no hardware dependencies, fully testable!
 */

#include "PneumaticController.h"

bool PneumaticController::calculatePistonState(HeightPosition position) {
    // HIGH position means pistons extended (true)
    // LOW position means pistons retracted (false)
    return (position == HIGH);
}

PneumaticController::HeightPosition PneumaticController::togglePosition(HeightPosition currentPosition) {
    // Switch to the opposite position
    return getOppositePosition(currentPosition);
}

PneumaticController::HeightPosition PneumaticController::getOppositePosition(HeightPosition position) {
    // Return LOW if position is HIGH, HIGH if position is LOW
    if (position == LOW) {
        return HIGH;
    } else {
        return LOW;
    }
}

