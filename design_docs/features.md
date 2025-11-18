# List of Features Needed

1. **Driving** ✅ (already coded)
   - 6-wheel drive train with 6 individual motors
   - Tank drive control
   - Tested and working

2. **Intake and Ramp System (Part 1)** 🚧
   - Intake mechanism: One 5.5V motor for ball intake
   - First two ramp wheels: Share one 5.5V motor (brings balls up the ramp)
   - These three motors work together to collect and transport balls

3. **Ramp System (Part 2)** 📋
   - Last ramp wheel: One full power motor (pushes balls out at top)
   - This is the final wheel in the three-wheel ramp system

4. **Height Adjustment System** 📋
   - Two pneumatic pistons
   - Adjust height of the full power wheel
   - Allows balls to be pushed out at two different heights

---

## Description of Robot

The robot has:
- **Drive train**: 6 wheels, each powered by 6 individual motors (✅ complete)
- **Intake mechanism**: Uses one 5.5V motor to collect balls
- **Ramp system**: Rubber bands lead up to three separate wheels with rubber bands for grip
  - First two wheels: Share one 5.5V motor (brings balls up)
  - Last wheel: Uses one full power motor (pushes balls out at top)
- **Height adjustment**: Two pneumatic pistons change the height of the full power wheel
  - Allows balls to be pushed out at two different heights

---

## Feature Breakdown & Implementation Plan

### Feature 2: Intake and Ramp System (Part 1) 🚧

**Motors Required:**
- 1x Intake Motor (5.5V) - Collects balls from ground
- 1x Ramp Motors (5.5V) - Powers first two ramp wheels (shared motor)

**Functionality:**
- Intake motor spins to collect balls
- Ramp motors spin to bring balls up the ramp
- Both can be controlled independently or together
- Need controller buttons/triggers to activate

**Implementation Steps:**
1. [ ] Write tests for IntakeController class (TDD - RED phase)
2. [ ] Implement basic IntakeController with motor declarations
3. [ ] Add intake control (forward/reverse/stop)
4. [ ] Add ramp control (forward/reverse/stop)
5. [ ] Integrate with controller buttons
6. [ ] Test on hardware

---

### Feature 3: Ramp System (Part 2) ✅

**Motors Required:**
- 1x Full Power Motor - Final ramp wheel (pushes balls out)

**Functionality:**
- Full power motor spins to push balls out at top of ramp
- Can be controlled independently
- Supports both full power mode (100%) and variable power mode

**Implementation Steps:**
1. [x] Write tests for RampController class (TDD - RED phase) ✅
2. [x] Implement full power motor control ✅
3. [x] Add speed control (full power vs variable) ✅
4. [ ] Integrate with controller (hardware integration next)
5. [ ] Test on hardware

---

### Feature 4: Height Adjustment System 📋

**Hardware Required:**
- 2x Pneumatic Pistons

**Functionality:**
- Pistons extend/retract to change height of full power wheel
- Two positions: Low height and High height
- Toggle between positions with controller button

**Implementation Steps:**
1. [ ] Write tests for PneumaticController class (TDD - RED phase)
2. [ ] Implement pneumatic piston control
3. [ ] Add position tracking (high/low)
4. [ ] Add toggle function
5. [ ] Integrate with controller
6. [ ] Test on hardware

---

## Next Steps

**Starting with Feature 2: Intake and Ramp System (Part 1)**

Let's implement this feature using TDD:
1. Create `IntakeController` class (testable logic)
2. Write unit tests first
3. Implement motor control
4. Integrate with main.cpp
5. Add controller button mapping
