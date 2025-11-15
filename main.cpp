/*
 * VEX V5 Robot - Basic Drive Train Control
 * 
 * This code demonstrates basic motor control for a robot's drive train.
 * The drive train typically consists of motors on the left and right sides
 * that work together to move the robot forward, backward, and turn.
 */

#include "main.h"  // Includes VEX library and standard headers
#include "DriveTrain.h"  // Our testable drive train logic

using namespace vex;  // Allows us to use VEX functions without typing "vex::"

// Initialize the VEX Brain controller (the main robot brain)
brain Brain;

// MOTOR DECLARATIONS
// Motors are named and assigned to specific ports on the V5 Brain
// The motor groups allow us to control multiple motors together

// Left side motors - these motors spin together to move the left side
motor LeftFrontMotor = motor(PORT1, ratio18_1, false);  
// motor: the type (like "int" or "string" but for VEX motors)
// LeftFrontMotor: the variable name we'll use to control this motor
// motor(...): the constructor that creates the motor object
//   PORT1: physical port number on the V5 Brain (where the motor is plugged in)
//   ratio18_1: gear ratio (18:1 means 18 motor rotations = 1 wheel rotation)
//   false: NOT reversed (set to true if the motor spins the wrong direction)
motor LeftBackMotor = motor(PORT2, ratio18_1, false);   // Port 2, gear ratio, reversed?
motor_group LeftDrive = motor_group(LeftFrontMotor, LeftBackMotor);  // Group them together

// Right side motors - these motors spin together to move the right side
motor RightFrontMotor = motor(PORT3, ratio18_1, true);  // Port 3, reversed for opposite spin
motor RightBackMotor = motor(PORT4, ratio18_1, true);   // Port 4, reversed for opposite spin
motor_group RightDrive = motor_group(RightFrontMotor, RightBackMotor);  // Group them together

// Controller - the V5 controller that the driver uses
controller Controller1 = controller(primary);

// Competition object - handles autonomous and driver control periods
competition Competition;

/**
 * Initialize your robot here.
 * This function runs once when the robot starts up.
 */
void vexcodeInit(void) {
  // Any initialization code goes here
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

