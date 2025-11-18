/*
 * VEX V5 Robot - Basic Drive Train Control
 * 
 * This code demonstrates basic motor control for a robot's drive train.
 * The drive train typically consists of motors on the left and right sides
 * that work together to move the robot forward, backward, and turn.
 */

#include "main.h"  // Includes VEX library and standard headers
#include "controllers/DriveTrain.h"  // Our testable drive train logic
#include "controllers/IntakeController.h"  // Intake and ramp motor control
#include "controllers/RampController.h"  // Full power ramp motor control
#include "controllers/PneumaticController.h"  // Pneumatic piston control

using namespace vex;  // Allows us to use VEX functions without typing "vex::"

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

