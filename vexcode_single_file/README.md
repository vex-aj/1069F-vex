# VEXcode Single File Version

## 📁 This Folder Contains

**`main.cpp`** - Complete robot code in a single file for VEXcode V5

This is a standalone version of all robot code that can be used directly in VEXcode V5 without needing multiple files or folders.

---

## 🚀 How to Use

### Step 1: Open VEXcode V5
1. Download VEXcode V5 from [codev5.vex.com](https://codev5.vex.com/)
2. Open VEXcode V5
3. Create new project: **File → New Project**
4. Choose: **"V5 Brain"**
5. Select: **"C++"** as programming language
6. Name it (e.g., "vex-iq")

### Step 2: Copy Code
1. Open `main.cpp` from this folder
2. Copy **ALL** content (Ctrl+A, Ctrl+C or Cmd+A, Cmd+C)
3. In VEXcode, open `main.cpp`
4. Select all (Ctrl+A or Cmd+A)
5. Paste the copied content (Ctrl+V or Cmd+V)

### Step 3: Build and Download
1. **Connect** V5 Brain via USB
2. **Power on** the Brain
3. Click **"Build"** button (should compile successfully)
4. Click **"Download"** button (uploads to robot)

### Step 4: Update Port Numbers
Before testing, **IMPORTANT**: Update port numbers in `main.cpp` to match your robot:

```cpp
// Drive Train (update PORT1-6 to match your wiring)
motor LeftFrontMotor = motor(PORT1, ratio18_1, false);
motor LeftMiddleMotor = motor(PORT2, ratio18_1, false);
// ... etc

// Intake & Ramp (update PORT7-9)
motor IntakeMotor = motor(PORT7, ratio18_1, false);
motor RampMotor = motor(PORT8, ratio18_1, false);
motor FullPowerRampMotor = motor(PORT9, ratio18_1, false);

// Pneumatics (update ThreeWirePort.A/B if needed)
digital_out Piston1 = digital_out(Brain.ThreeWirePort.A);
digital_out Piston2 = digital_out(Brain.ThreeWirePort.B);
```

---

## ✅ What's Included

This single file contains:

- ✅ **DriveTrain class** - Tank drive and arcade drive calculations
- ✅ **IntakeController class** - Intake and ramp motor control (5.5V motors)
- ✅ **RampController class** - Full power ramp motor control
- ✅ **PneumaticController class** - Height adjustment system
- ✅ **All hardware declarations** - Motors, pistons, controller, brain
- ✅ **Autonomous function** - Example autonomous routine
- ✅ **User control function** - Complete driver control with all features
- ✅ **Main function** - Competition mode setup

---

## 🎮 Controller Mapping

- **Left Stick (Y)**: Left side drive motors
- **Right Stick (Y)**: Right side drive motors
- **R1**: Intake forward (collect balls)
- **R2**: Intake reverse (spit out)
- **L1**: Ramp forward (bring balls up)
- **L2**: Ramp reverse (bring balls down)
- **X**: Full power ramp forward (push balls out)
- **Y**: Full power ramp reverse (pull balls back)
- **A**: Toggle pneumatic height (LOW ↔ HIGH)

---

## 📝 Notes

- All controller logic is defined inline in this file
- No separate header files needed
- No folders needed - just paste into VEXcode's main.cpp
- Code is well-commented and organized
- Same functionality as the multi-file version

---

## 🐛 Troubleshooting

### Build Errors
- Check that you copied the entire file
- Verify VEXcode is set to C++ (not Blocks)
- Try cleaning and rebuilding

### Upload Fails
- Check USB connection
- Power on the Brain
- Try different USB port
- Restart VEXcode

### Robot Doesn't Move
- **Check port numbers** match your robot wiring
- Verify motors are plugged in
- Check motor reversal flags (`true`/`false`)
- Test with simple motor spin first

---

**Ready to deploy! Just copy, paste, build, and download!** 🤖

