/*
 * DriveTrain.h
 * 
 * This header defines the DriveTrain class, which encapsulates all drive train logic.
 * By separating this from the hardware, we can test the logic without needing actual motors.
 * 
 * This follows Test-Driven Development (TDD) principles:
 * - Single Responsibility: DriveTrain only handles drive calculations
 * - Dependency Inversion: Logic is independent of specific motor implementations
 * - Testability: Pure functions can be unit tested easily
 */

#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

/**
 * DriveTrain Class
 * 
 * Handles all drive train calculations and logic.
 * This class is designed to be easily testable - it doesn't directly control hardware.
 * Instead, it calculates what the motors should do, and returns those values.
 */
class DriveTrain {
public:
    /**
     * Calculate tank drive motor powers
     * 
     * Pure function: same input always produces same output (easy to test!)
     * 
     * @param leftStickInput Input from left stick (-100 to 100)
     * @param rightStickInput Input from right stick (-100 to 100)
     * @param leftPower Output parameter for left motor power (-100 to 100)
     * @param rightPower Output parameter for right motor power (-100 to 100)
     */
    static void calculateTankDrive(int leftStickInput, int rightStickInput, 
                                   int& leftPower, int& rightPower);
    
    /**
     * Calculate arcade drive motor powers
     * 
     * Pure function: converts forward/turn input to left/right motor powers
     * 
     * @param forwardInput Forward/backward input (-100 to 100)
     * @param turnInput Left/right turn input (-100 to 100)
     * @param leftPower Output parameter for left motor power (-100 to 100)
     * @param rightPower Output parameter for right motor power (-100 to 100)
     */
    static void calculateArcadeDrive(int forwardInput, int turnInput,
                                     int& leftPower, int& rightPower);
    
    /**
     * Clamp a value to be within a specific range
     * 
     * Pure function: ensures values stay within bounds
     * 
     * @param value The value to clamp
     * @param min The minimum allowed value
     * @param max The maximum allowed value
     * @return The clamped value
     */
    static int clamp(int value, int min, int max);
    
    /**
     * Apply deadband to controller input
     * 
     * Prevents small controller drift from moving the robot
     * 
     * @param input The controller input value
     * @param deadband The deadband threshold (typically 5-10)
     * @return The input value, or 0 if within deadband
     */
    static int applyDeadband(int input, int deadband);
};

#endif // DRIVETRAIN_H

