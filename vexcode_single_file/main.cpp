/*
 * VEX V5 Robot - Complete Robot Code (Single File for VEXcode)
 * 
 * This is a single-file version of the robot code for use with VEXcode V5.
 * All controller classes are defined inline in this file.
 * 
 * To use this file:
 * 1. Open VEXcode V5
 * 2. Create new C++ project
 * 3. Replace the default main.cpp with this file's contents
 * 4. Build and download to robot
 */

#include "vex.h"  // VEX library (VEXcode includes this automatically)

using namespace vex;  // Allows us to use VEX functions without typing "vex::"

// ============================================================================
// CONTROLLER CLASSES - All logic defined inline here
// ============================================================================

// ----------------------------------------------------------------------------
// DriveTrain Class
// ----------------------------------------------------------------------------
/**
 * DriveTrain Class
 * 
 * Handles all drive train calculations and logic.
 * Pure functions - no hardware dependencies, fully testable!
 */
class DriveTrain {
public:
    /**
     * Calculate tank drive motor powers
     * 
     * Pure function: same input always produces same output
     * 
     * @param leftStickInput Input from left stick (-100 to 100)
     * @param rightStickInput Input from right stick (-100 to 100)
     * @param leftPower Output parameter for left motor power (-100 to 100)
     * @param rightPower Output parameter for right motor power (-100 to 100)
     */
    static void calculateTankDrive(int leftStickInput, int rightStickInput, 
                                   int& leftPower, int& rightPower) {
        // Tank drive is simple: left stick controls left motors, right stick controls right motors
        leftPower = clamp(leftStickInput, -100, 100);
        rightPower = clamp(rightStickInput, -100, 100);
    }
    
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
                                     int& leftPower, int& rightPower) {
        // Arcade drive: forward controls speed, turn controls direction
        // Formula: left = forward + turn, right = forward - turn
        
        leftPower = forwardInput + turnInput;   // Add turn to forward
        rightPower = forwardInput - turnInput;  // Subtract turn from forward
        
        // Ensure values stay within -100 to 100 range
        leftPower = clamp(leftPower, -100, 100);
        rightPower = clamp(rightPower, -100, 100);
    }
    
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
    static int clamp(int value, int min, int max) {
        if (value < min) {
            return min;
        }
        if (value > max) {
            return max;
        }
        return value;
    }
    
    /**
     * Apply deadband to controller input
     * 
     * Prevents small controller drift from moving the robot
     * 
     * @param input The controller input value
     * @param deadband The deadband threshold (typically 5-10)
     * @return The input value, or 0 if within deadband
     */
    static int applyDeadband(int input, int deadband) {
        // If input is within deadband range, return 0 (prevents small drift)
        if (input > -deadband && input < deadband) {
            return 0;
        }
        return input;
    }
};

// ----------------------------------------------------------------------------
// IntakeController Class
// ----------------------------------------------------------------------------
/**
 * IntakeController Class
 * 
 * Handles intake and ramp motor control logic.
 * Pure functions - no hardware dependencies, fully testable!
 */
class IntakeController {
public:
    /**
     * Motor power states
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
    static int calculateIntakePower(MotorState state, int powerLevel) {
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
    
    /**
     * Calculate ramp motor power
     * 
     * Pure function: converts motor state to power value
     * 
     * @param state The desired motor state (STOP, FORWARD, REVERSE)
     * @param powerLevel The power level (0-100) for forward/reverse, ignored for STOP
     * @return Motor power value (-100 to 100, where 0 = stop)
     */
    static int calculateRampPower(MotorState state, int powerLevel) {
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
    
    /**
     * Clamp power level to valid range
     * 
     * Pure function: ensures power level stays within 0-100
     * 
     * @param powerLevel The power level to clamp
     * @return Clamped power level (0-100)
     */
    static int clampPowerLevel(int powerLevel) {
        // Ensure power level stays within 0-100 range
        if (powerLevel < 0) {
            return 0;
        }
        if (powerLevel > 100) {
            return 100;
        }
        return powerLevel;
    }
};

// ----------------------------------------------------------------------------
// RampController Class
// ----------------------------------------------------------------------------
/**
 * RampController Class
 * 
 * Handles full power ramp motor control logic.
 * This is for the final ramp wheel that pushes balls out at the top.
 * Pure functions - no hardware dependencies, fully testable!
 */
class RampController {
public:
    /**
     * Motor power states
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
    static int calculateRampPower(MotorState state, bool useFullPower, int powerLevel) {
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
    
    /**
     * Clamp power level to valid range
     * 
     * Pure function: ensures power level stays within 0-100
     * 
     * @param powerLevel The power level to clamp
     * @return Clamped power level (0-100)
     */
    static int clampPowerLevel(int powerLevel) {
        // Ensure power level stays within 0-100 range
        if (powerLevel < 0) {
            return 0;
        }
        if (powerLevel > 100) {
            return 100;
        }
        return powerLevel;
    }
};

// ----------------------------------------------------------------------------
// PneumaticController Class
// ----------------------------------------------------------------------------
/**
 * PneumaticController Class
 * 
 * Handles pneumatic piston control logic for height adjustment.
 * Two pistons work together to adjust the height of the full power ramp wheel.
 * Pure functions - no hardware dependencies, fully testable!
 */
class PneumaticController {
public:
    /**
     * Height positions
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
    static bool calculatePistonState(HeightPosition position) {
        // HIGH position means pistons extended (true)
        // LOW position means pistons retracted (false)
        return (position == HIGH);
    }
    
    /**
     * Toggle height position
     * 
     * Pure function: switches between LOW and HIGH positions
     * 
     * @param currentPosition The current height position
     * @return The new height position (opposite of current)
     */
    static HeightPosition togglePosition(HeightPosition currentPosition) {
        // Switch to the opposite position
        return getOppositePosition(currentPosition);
    }
    
    /**
     * Get opposite position
     * 
     * Pure function: returns the opposite of the given position
     * 
     * @param position The current position
     * @return LOW if position is HIGH, HIGH if position is LOW
     */
    static HeightPosition getOppositePosition(HeightPosition position) {
        // Return LOW if position is HIGH, HIGH if position is LOW
        if (position == LOW) {
            return HIGH;
        } else {
            return LOW;
        }
    }
};

// ============================================================================
// HARDWARE DECLARATIONS
// ============================================================================

// Initialize the VEX Brain controller (the main robot brain)
brain Brain;

// MOTOR DECLARATIONS
// Motors are named and assigned to specific ports on the V5 Brain
// The motor groups allow us to control multiple motors together

// Left side motors - 3 motors that spin together to move the left side
motor LeftFrontMotor = motor(PORT1, ratio18_1, false);  
// motor: the type (like "int" or "string" but for VEX motors)
// LeftFrontMotor: the variable name we'll use to control this motor
// motor(...): the constructor that creates the motor object
//   PORT1: physical port number on the V5 Brain (where the motor is plugged in)
//   ratio18_1: gear ratio (18:1 means 18 motor rotations = 1 wheel rotation)
//   false: NOT reversed (set to true if the motor spins the wrong direction)
motor LeftMiddleMotor = motor(PORT2, ratio18_1, false);   // Port 2, middle left motor
motor LeftBackMotor = motor(PORT3, ratio18_1, false);   // Port 3, back left motor
motor_group LeftDrive = motor_group(LeftFrontMotor, LeftMiddleMotor, LeftBackMotor);  // Group all 3 together

// Right side motors - 3 motors that spin together to move the right side
motor RightFrontMotor = motor(PORT4, ratio18_1, true);  // Port 4, reversed for opposite spin
motor RightMiddleMotor = motor(PORT5, ratio18_1, true);  // Port 5, middle right motor, reversed
motor RightBackMotor = motor(PORT6, ratio18_1, true);   // Port 6, back right motor, reversed
motor_group RightDrive = motor_group(RightFrontMotor, RightMiddleMotor, RightBackMotor);  // Group all 3 together

// INTAKE AND RAMP MOTORS (Feature 2)
// Intake motor - collects balls from ground (5.5V motor)
motor IntakeMotor = motor(PORT7, ratio18_1, false);  // Port 7, adjust port and reversal as needed

// Ramp motors - first two ramp wheels share one motor (5.5V motor)
motor RampMotor = motor(PORT8, ratio18_1, false);  // Port 8, adjust port and reversal as needed

// FULL POWER RAMP MOTOR (Feature 3)
// Final ramp wheel - pushes balls out at top (full power motor)
motor FullPowerRampMotor = motor(PORT9, ratio18_1, false);  // Port 9, adjust port and reversal as needed

// PNEUMATIC PISTONS (Feature 4)
// Two pneumatic pistons control height of full power wheel
// Note: Adjust port numbers to match your robot's wiring
digital_out Piston1 = digital_out(Brain.ThreeWirePort.A);  // First piston
digital_out Piston2 = digital_out(Brain.ThreeWirePort.B);  // Second piston

// Controller - the V5 controller that the driver uses
controller Controller1 = controller(primary);

// Competition object - handles autonomous and driver control periods
competition Competition;

// PNEUMATIC STATE TRACKING
// Track current height position for pneumatic pistons
PneumaticController::HeightPosition currentHeight = PneumaticController::LOW;  // Start at low position
bool lastToggleButtonState = false;  // Track button state to detect presses (not holds)

/**
 * Initialize your robot here.
 * This function runs once when the robot starts up.
 */
void vexcodeInit(void) {
  // Initialize pneumatic pistons to LOW position (retracted)
  // This ensures the robot starts at low height
  bool initialPistonState = PneumaticController::calculatePistonState(PneumaticController::LOW);
  Piston1.set(initialPistonState);
  Piston2.set(initialPistonState);
  currentHeight = PneumaticController::LOW;  // Set initial state
  
  // Any other initialization code goes here
  // This is called before the competition starts
}

/**
 * AUTONOMOUS MODE
 * This function runs when the robot is in autonomous mode (no driver).
 * Write code here for your robot to run by itself.
 */
void autonomous(void) {
  // Example: Move forward for 2 seconds, then stop
  LeftDrive.spin(forward, 50, percent);   // Left motors at 50% power forward
  RightDrive.spin(forward, 50, percent);  // Right motors at 50% power forward
  wait(2000, msec);  // Wait 2000 milliseconds (2 seconds)
  
  // Stop the motors
  LeftDrive.stop();
  RightDrive.stop();
}

/**
 * USER CONTROL MODE (DRIVER CONTROL)
 * This function runs continuously while the driver controls the robot.
 */
void usercontrol(void) {
  // This loop runs forever while the robot is in driver control mode
  while (true) {
    
    // OPTION 1: TANK DRIVE
    // Driver uses left stick for left motors, right stick for right motors
    // This is like a tank - each side moves independently
    
    // Read controller stick values (-100 to +100)
    int leftStickInput = Controller1.Axis3.position();   // Left stick vertical axis (Y)
    int rightStickInput = Controller1.Axis2.position();  // Right stick vertical axis (Y)
    // Note: Axis3 = Left stick Y, Axis2 = Right stick Y
    // If this doesn't work, try Axis4 for right stick instead of Axis2
    
    // Apply deadband to prevent drift (removes small unwanted movements)
    leftStickInput = DriveTrain::applyDeadband(leftStickInput, 5);
    rightStickInput = DriveTrain::applyDeadband(rightStickInput, 5);
    
    // Calculate motor powers using our testable DriveTrain class
    int leftPower, rightPower;
    DriveTrain::calculateTankDrive(leftStickInput, rightStickInput, leftPower, rightPower);
    
    // Set motor speeds to calculated values
    LeftDrive.spin(forward, leftPower, percent);   // Left motors
    RightDrive.spin(forward, rightPower, percent); // Right motors
    
    // ============================================
    // INTAKE AND RAMP CONTROL (Feature 2)
    // ============================================
    
    // Intake Motor Control
    // R1 = Intake forward (collect balls), R2 = Intake reverse (spit out)
    IntakeController::MotorState intakeState = IntakeController::STOP;
    if (Controller1.ButtonR1.pressing()) {
        intakeState = IntakeController::FORWARD;  // Collect balls
    } else if (Controller1.ButtonR2.pressing()) {
        intakeState = IntakeController::REVERSE;  // Spit out
    }
    
    // Calculate intake motor power using our testable IntakeController
    int intakePower = IntakeController::calculateIntakePower(intakeState, 100);  // 100% power
    IntakeMotor.spin(forward, intakePower, percent);
    
    // Ramp Motor Control (first two wheels)
    // L1 = Ramp forward (bring balls up), L2 = Ramp reverse (bring balls down)
    IntakeController::MotorState rampState = IntakeController::STOP;
    if (Controller1.ButtonL1.pressing()) {
        rampState = IntakeController::FORWARD;  // Bring balls up
    } else if (Controller1.ButtonL2.pressing()) {
        rampState = IntakeController::REVERSE;  // Bring balls down
    }
    
    // Calculate ramp motor power using our testable IntakeController
    int rampPower = IntakeController::calculateRampPower(rampState, 100);  // 100% power
    RampMotor.spin(forward, rampPower, percent);
    
    // ============================================
    // FULL POWER RAMP MOTOR CONTROL (Feature 3)
    // ============================================
    
    // Full Power Ramp Motor Control
    // X = Full power forward (push balls out), Y = Full power reverse
    RampController::MotorState fullPowerState = RampController::STOP;
    if (Controller1.ButtonX.pressing()) {
        fullPowerState = RampController::FORWARD;  // Push balls out
    } else if (Controller1.ButtonY.pressing()) {
        fullPowerState = RampController::REVERSE;  // Pull balls back
    }
    
    // Calculate full power ramp motor power using our testable RampController
    // Use full power mode (100% when active)
    int fullPowerRampPower = RampController::calculateRampPower(fullPowerState, true, 0);
    FullPowerRampMotor.spin(forward, fullPowerRampPower, percent);
    
    // ============================================
    // PNEUMATIC HEIGHT CONTROL (Feature 4)
    // ============================================
    
    // Toggle height position with Button A
    // Detect button press (not hold) to toggle once per press
    bool currentToggleButton = Controller1.ButtonA.pressing();
    if (currentToggleButton && !lastToggleButtonState) {
        // Button was just pressed (edge detection)
        // Toggle to opposite position
        currentHeight = PneumaticController::togglePosition(currentHeight);
        
        // Calculate piston state (true = extended, false = retracted)
        bool pistonState = PneumaticController::calculatePistonState(currentHeight);
        
        // Set both pistons to the same state
        Piston1.set(pistonState);
        Piston2.set(pistonState);
    }
    lastToggleButtonState = currentToggleButton;  // Remember state for next loop
    
    // OPTION 2: ARCADE DRIVE (COMMENTED OUT - UNCOMMENT TO USE)
    // Driver uses one stick: forward/backward controls speed, left/right controls turning
    // This is more like a car - more intuitive for some drivers
    
    /*
    // Read controller input
    int forwardInput = Controller1.Axis3.position();    // Forward/backward
    int turnInput = Controller1.Axis1.position();       // Left/right turning
    
    // Apply deadband to prevent drift
    forwardInput = DriveTrain::applyDeadband(forwardInput, 5);
    turnInput = DriveTrain::applyDeadband(turnInput, 5);
    
    // Calculate left and right motor powers using our testable DriveTrain class
    int leftPowerArcade, rightPowerArcade;
    DriveTrain::calculateArcadeDrive(forwardInput, turnInput, leftPowerArcade, rightPowerArcade);
    
    // Set motor speeds (clamping is handled inside calculateArcadeDrive!)
    LeftDrive.spin(forward, leftPowerArcade, percent);
    RightDrive.spin(forward, rightPowerArcade, percent);
    */
    
    // Small delay to prevent the loop from running too fast
    // This gives the motors time to respond and saves processing power
    wait(20, msec);  // Wait 20 milliseconds between loop cycles
  }
}

/**
 * MAIN FUNCTION
 * This is where the program starts when the robot turns on.
 */
int main() {
  // Initialize the robot
  vexcodeInit();
  
  // Competition mode (for competitions)
  Competition.autonomous(autonomous);   // Run autonomous() during autonomous period
  Competition.drivercontrol(usercontrol); // Run usercontrol() during driver control
  
  // If NOT in competition, uncomment one of these:
  // autonomous();  // Run autonomous code once
  // usercontrol(); // Run driver control code (keeps running)
  
  // Prevent the program from exiting
  while (true) {
    wait(100, msec);  // Wait and repeat
  }
}

