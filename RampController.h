/*
 * RampController.h
 * 
 * This header defines the RampController class, which handles the full power ramp motor control.
 * This is for the final ramp wheel that pushes balls out at the top of the robot.
 * By separating this from the hardware, we can test the logic without needing actual motors.
 * 
 * This follows Test-Driven Development (TDD) principles:
 * - Single Responsibility: RampController only handles full power ramp calculations
 * - Dependency Inversion: Logic is independent of specific motor implementations
 * - Testability: Pure functions can be unit tested easily
 */

#ifndef RAMPCONTROLLER_H
#define RAMPCONTROLLER_H

/**
 * RampController Class
 * 
 * Handles full power ramp motor control logic.
 * This class is designed to be easily testable - it doesn't directly control hardware.
 * Instead, it calculates what the motor should do, and returns those values.
 * 
 * Note: This is for the final ramp wheel (full power motor) that pushes balls out.
 * The first two ramp wheels are controlled by IntakeController.
 */
class RampController {
public:
    /**
     * Motor power states
     * Used to represent the desired state of the full power ramp motor
     */
    enum MotorState {
        STOP = 0,      // Motor stopped
        FORWARD = 1,   // Motor spinning forward (push balls out)
        REVERSE = -1   // Motor spinning reverse (pull balls back)
    };
    
    /**
     * Calculate full power ramp motor power
     * 
     * Pure function: converts motor state to power value
     * This motor uses full power (100%) when active, unlike the 5.5V motors
     * 
     * @param state The desired motor state (STOP, FORWARD, REVERSE)
     * @param useFullPower If true, uses 100% power when forward/reverse. If false, uses variable power level
     * @param powerLevel The power level (0-100) for variable power mode, ignored if useFullPower is true
     * @return Motor power value (-100 to 100, where 0 = stop)
     */
    static int calculateRampPower(MotorState state, bool useFullPower, int powerLevel);
    
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

#endif // RAMPCONTROLLER_H

