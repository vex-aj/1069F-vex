/*
 * PneumaticController.h
 * 
 * This header defines the PneumaticController class, which handles pneumatic piston control.
 * Two pistons work together to adjust the height of the full power ramp wheel.
 * By separating this from the hardware, we can test the logic without needing actual pistons.
 * 
 * This follows Test-Driven Development (TDD) principles:
 * - Single Responsibility: PneumaticController only handles height position logic
 * - Dependency Inversion: Logic is independent of specific hardware implementations
 * - Testability: Pure functions can be unit tested easily
 */

#ifndef PNEUMATICCONTROLLER_H
#define PNEUMATICCONTROLLER_H

/**
 * PneumaticController Class
 * 
 * Handles pneumatic piston control logic for height adjustment.
 * This class is designed to be easily testable - it doesn't directly control hardware.
 * Instead, it calculates what the pistons should do, and returns those values.
 */
class PneumaticController {
public:
    /**
     * Height positions
     * Used to represent the desired height of the ramp wheel
     */
    enum HeightPosition {
        LOW = 0,   // Pistons retracted (low height)
        HIGH = 1   // Pistons extended (high height)
    };
    
    /**
     * Calculate piston state from height position
     * 
     * Pure function: converts height position to piston state
     * 
     * @param position The desired height position (LOW or HIGH)
     * @return true if pistons should be extended (HIGH), false if retracted (LOW)
     */
    static bool calculatePistonState(HeightPosition position);
    
    /**
     * Toggle height position
     * 
     * Pure function: switches between LOW and HIGH positions
     * 
     * @param currentPosition The current height position
     * @return The new height position (opposite of current)
     */
    static HeightPosition togglePosition(HeightPosition currentPosition);
    
    /**
     * Get opposite position
     * 
     * Pure function: returns the opposite of the given position
     * 
     * @param position The current position
     * @return LOW if position is HIGH, HIGH if position is LOW
     */
    static HeightPosition getOppositePosition(HeightPosition position);
};

#endif // PNEUMATICCONTROLLER_H

