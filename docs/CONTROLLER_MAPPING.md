# Controller Button Mapping

## Drive Train
- **Left Stick (Y-axis)**: Left side motors forward/backward
- **Right Stick (Y-axis)**: Right side motors forward/backward
- **Tank Drive**: Each stick controls its respective side independently

## Intake System (Feature 2)
- **R1 Button**: Intake forward (collect balls) - 100% power
- **R2 Button**: Intake reverse (spit out) - 100% power
- **Released**: Intake stops

## Ramp System - First Two Wheels (Feature 2)
- **L1 Button**: Ramp forward (bring balls up) - 100% power
- **L2 Button**: Ramp reverse (bring balls down) - 100% power
- **Released**: Ramp stops

## Ramp System - Final Wheel (Feature 3)
- **X Button**: Full power forward (push balls out) - 100% power
- **Y Button**: Full power reverse (pull balls back) - 100% power
- **Released**: Full power ramp stops

## Height Adjustment (Feature 4)
- **A Button**: Toggle height position (LOW ↔ HIGH)
  - Press once: Switch to opposite position
  - Uses edge detection (only toggles on button press, not hold)
  - Both pistons move together

## Button Layout Summary

```
Controller Layout:
┌─────────────────┐
│  [L1]  [L2]     │  L1/L2: Ramp (first two wheels)
│                 │
│  [Left Stick]   │  Left Stick: Left drive motors
│                 │
│  [A] [B] [X] [Y]│  A: Toggle height
│                 │  X/Y: Full power ramp
│  [Right Stick]  │  Right Stick: Right drive motors
│                 │
│  [R1]  [R2]     │  R1/R2: Intake
└─────────────────┘
```

## Motor Port Assignments

**IMPORTANT**: Update these port numbers to match your robot's wiring!

- **Drive Train** (6 motors total - 3 per side):
  - Left Front: PORT1
  - Left Middle: PORT2
  - Left Back: PORT3
  - Right Front: PORT4
  - Right Middle: PORT5
  - Right Back: PORT6

- **Intake & Ramp**:
  - Intake Motor: PORT7 (5.5V)
  - Ramp Motor (first two wheels): PORT8 (5.5V)
  - Full Power Ramp Motor: PORT9 (full power)

- **Pneumatics**:
  - Piston 1: ThreeWirePort.A
  - Piston 2: ThreeWirePort.B

## Customization

To change button mappings, edit `src/main.cpp` in the `usercontrol()` function:

```cpp
// Example: Change intake to different buttons
if (Controller1.ButtonUp.pressing()) {  // Instead of ButtonR1
    intakeState = IntakeController::FORWARD;
}
```

## Power Levels

- **Intake & Ramp (5.5V motors)**: 100% power (can be adjusted in code)
- **Full Power Ramp**: 100% power (full power mode)
- **Drive Train**: Variable based on stick position (0-100%)

## Notes

- All motors stop when buttons are released
- Pneumatic toggle uses edge detection (only toggles once per button press)
- Deadband is applied to drive train sticks to prevent drift
- All logic uses testable controller classes (DriveTrain, IntakeController, RampController, PneumaticController)

