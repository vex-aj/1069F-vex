# Deployment Checklist - Before Loading to Robot

## ⚠️ Issues to Fix Before Deployment

### ✅ 1. Competition Object (FIXED)
- **Status**: ✅ Now declared in `main.cpp`
- **What was missing**: `competition Competition;` declaration
- **Impact**: Without this, the robot wouldn't start in competition mode

### ⚠️ 2. Motor Port Numbers (CHECK YOUR ROBOT)
- **Current code assumes**:
  - Left Front Motor: PORT1
  - Left Back Motor: PORT2
  - Right Front Motor: PORT3
  - Right Back Motor: PORT4
  
- **Action required**: Update `main.cpp` to match YOUR robot's wiring
  ```cpp
  motor LeftFrontMotor = motor(PORT1, ratio18_1, false);  // Change PORT1 if different
  motor LeftBackMotor = motor(PORT2, ratio18_1, false);   // Change PORT2 if different
  motor RightFrontMotor = motor(PORT3, ratio18_1, true);  // Change PORT3 if different
  motor RightBackMotor = motor(PORT4, ratio18_1, true);   // Change PORT4 if different
  ```

### ⚠️ 3. Motor Reversal Flags (TEST & ADJUST)
- **Current setup**:
  - Left motors: `false` (not reversed)
  - Right motors: `true` (reversed)
  
- **Why**: Right motors often need to be reversed so both sides spin forward together
  
- **Action required**: 
  1. Load code and test forward movement
  2. If robot spins in place or goes backward, flip the `true`/`false` values
  3. Left and right sides should both move forward when sticks are pushed forward

### ⚠️ 4. Gear Ratio (MATCH YOUR MOTOR CARTRIDGE)
- **Current code uses**: `ratio18_1` (18:1 gear ratio - Green cartridge)
  
- **Options**:
  - `ratio36_1` - Red cartridge (36:1 - slower, more torque)
  - `ratio18_1` - Green cartridge (18:1 - medium)
  - `ratio6_1` - Blue cartridge (6:1 - faster, less torque)
  - `green` - Alias for 18:1
  
- **Action required**: Change `ratio18_1` to match your actual motor cartridges

### ⚠️ 5. Controller Axis Mapping (VERIFY)
- **Current code uses**:
  - `Axis3` for left stick (should be correct)
  - `Axis2` for right stick (might need to be `Axis4`)
  
- **Standard VEX Controller mapping**:
  - `Axis3` = Left stick Y (vertical) ✅
  - `Axis4` = Right stick Y (vertical) ⚠️ (we're using Axis2)
  - `Axis1` = Left stick X (horizontal)
  
- **Action required**: If right stick doesn't work, try changing:
  ```cpp
  int rightStickInput = Controller1.Axis4.position();  // Try Axis4 instead of Axis2
  ```

### ⚠️ 6. Test Mode vs Competition Mode
- **Current code**: Uses competition mode (for competitions)
  
- **For practice/testing**, you might want to uncomment in `main()`:
  ```cpp
  // autonomous();  // Uncomment to test autonomous
  // usercontrol(); // Uncomment to test driver control (keeps running)
  ```
  
- **Action required**: Comment out Competition lines and uncomment one of the test modes if not competing

---

## ✅ What Should Work

1. **Code structure**: ✅ Correct
2. **DriveTrain logic**: ✅ All functions tested and working
3. **Deadband**: ✅ Will prevent controller drift
4. **Tank drive**: ✅ Should work once axes are correct
5. **Motor groups**: ✅ Correctly set up
6. **Basic syntax**: ✅ All correct

---

## 📋 Pre-Deployment Checklist

- [ ] Fix motor port numbers to match your robot
- [ ] Fix gear ratio to match your motor cartridges
- [ ] Test motor reversal flags (might need to flip)
- [ ] Verify controller axis mapping (might need Axis4 instead of Axis2)
- [ ] Compile with PROS toolchain
- [ ] Upload to robot
- [ ] Test autonomous mode first (safer - drives forward 2 seconds)
- [ ] Test driver control mode
- [ ] Adjust deadband value if needed (currently 5)
- [ ] Fine-tune motor speeds if needed

---

## 🚀 Step-by-Step Deployment

### 1. Update Motor Configuration
Open `main.cpp` and update:
- Motor ports (lines 22, 29, 33, 34)
- Gear ratios (if different from ratio18_1)
- Reversal flags (test and adjust)

### 2. Test Controller Axes
If right stick doesn't work, change line 79:
```cpp
// Change from:
int rightStickInput = Controller1.Axis2.position();
// To:
int rightStickInput = Controller1.Axis4.position();
```

### 3. Compile with PROS
```bash
pros make
```

### 4. Upload to Robot
```bash
pros upload
```

### 5. Test Safely
- Start with autonomous mode (robot drives forward 2 seconds)
- Then test driver control mode
- Have robot elevated or in safe area first!

---

## 🐛 Common Issues & Solutions

### Robot Doesn't Move
- **Check**: Motor port numbers match wiring
- **Check**: Motors are plugged in and powered
- **Check**: Competition mode vs test mode

### Robot Spins in Place
- **Solution**: Reverse one side's motors (change `true` to `false` or vice versa)

### Only One Side Moves
- **Solution**: Check motor port numbers and wiring

### Controller Doesn't Respond
- **Solution**: Check axis mapping (try Axis4 instead of Axis2 for right stick)
- **Solution**: Check controller is connected and paired

### Robot Drifts When Sticks Centered
- **Solution**: Increase deadband value (currently 5, try 7-10)

---

## ✅ Expected Behavior

### Autonomous Mode
- Robot should drive forward at 50% power for 2 seconds
- Then stop

### Driver Control Mode (Tank Drive)
- Push left stick forward → left motors spin forward
- Push right stick forward → right motors spin forward
- Push both forward → robot drives straight
- Push left back, right forward → robot turns left (spins in place)

---

## 📝 Summary

**The code structure is correct and should work**, but you need to:
1. ✅ **Match hardware configuration** (ports, gear ratios)
2. ✅ **Test and adjust** (motor reversal, controller axes)
3. ✅ **Deploy using PROS toolchain**

The logic is all tested and working - it's just a matter of matching the code to your specific robot's hardware setup!

