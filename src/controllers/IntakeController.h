/*
 * IntakeController.h
 * 
 * This header defines the IntakeController class, which handles intake and ramp motor control.
 * By separating this from the hardware, we can test the logic without needing actual motors.
 * 
 * This follows Test-Driven Development (TDD) principles:
 * - Single Responsibility: IntakeController only handles intake/ramp calculations
 * - Dependency Inversion: Logic is independent of specific motor implementations
 * - Testability: Pure functions can be unit tested easily
 */

#ifndef INTAKECONTROLLER_H
#define INTAKECONTROLLER_H

/**
 * IntakeController Class
 * 
 * Handles intake and ramp motor control logic.
 * This class is designed to be easily testable - it doesn't directly control hardware.
 * Instead, it calculates what the motors should do, and returns those values.
 */
class IntakeController {
public:
    /**
     * Motor power states
     * Used to represent the desired state of a motor
     */
    enum MotorState {
        STOP = 0,      // Motor stopped
        FORWARD = 1,   // Motor spinning forward (intake/ramp up)
        REVERSE = -1   // Motor spinning reverse (spit out/ramp down)
    };
    
    /**
     * Calculate intake motor power
     * 
     * Pure function: converts motor state to power value
     * 
     * @param state The desired motor state (STOP, FORWARD, REVERSE)
     * @param powerLevel The power level (0-100) for forward/reverse, ignored for STOP
     * @return Motor power value (-100 to 100, where 0 = stop)
     */
    static int calculateIntakePower(MotorState state, int powerLevel);
    
    /**
     * Calculate ramp motor power
     * 
     * Pure function: converts motor state to power value
     * 
     * @param state The desired motor state (STOP, FORWARD, REVERSE)
     * @param powerLevel The power level (0-100) for forward/reverse, ignored for STOP
     * @return Motor power value (-100 to 100, where 0 = stop)
     */
    static int calculateRampPower(MotorState state, int powerLevel);
    
    /**
     * Clamp power level to valid range
     * 
     * Pure function: ensures power level stays within 0-100
     * 
     * @param powerLevel The power level to clamp
     * @return Clamped power level (0-100)
     */
    static int clampPowerLevel(int powerLevel);
};

#endif // INTAKECONTROLLER_H

