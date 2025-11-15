/*
 * DriveTrain.cpp
 * 
 * Implementation of drive train logic.
 * These are pure functions - no hardware dependencies, fully testable!
 */

#include "DriveTrain.h"

void DriveTrain::calculateTankDrive(int leftStickInput, int rightStickInput, 
                                     int& leftPower, int& rightPower) {
    // Tank drive is simple: left stick controls left motors, right stick controls right motors
    leftPower = clamp(leftStickInput, -100, 100);
    rightPower = clamp(rightStickInput, -100, 100);
}

void DriveTrain::calculateArcadeDrive(int forwardInput, int turnInput,
                                       int& leftPower, int& rightPower) {
    // Arcade drive: forward controls speed, turn controls direction
    // When turning left: left motor slows down, right motor speeds up (or vice versa)
    // Formula: left = forward + turn, right = forward - turn
    
    leftPower = forwardInput + turnInput;   // Add turn to forward
    rightPower = forwardInput - turnInput;  // Subtract turn from forward
    
    // Ensure values stay within -100 to 100 range
    leftPower = clamp(leftPower, -100, 100);
    rightPower = clamp(rightPower, -100, 100);
}

int DriveTrain::clamp(int value, int min, int max) {
    if (value < min) {
        return min;
    }
    if (value > max) {
        return max;
    }
    return value;
}

int DriveTrain::applyDeadband(int input, int deadband) {
    // If input is within deadband range, return 0 (prevents small drift)
    if (input > -deadband && input < deadband) {
        return 0;
    }
    return input;
}

