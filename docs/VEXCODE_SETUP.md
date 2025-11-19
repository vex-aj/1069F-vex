# VEXcode V5 Setup - Step by Step Guide

## Quick Setup for VEXcode V5 IDE

This is the easiest alternative to PROS for deploying your code.

## ⚡ Quick Start (Recommended)

**For the easiest setup, use the single-file version:**

1. Go to `vexcode_single_file/main.cpp` in this project
2. Copy the entire file contents
3. Paste into VEXcode's main.cpp
4. Build and download!

See `vexcode_single_file/README.md` for detailed instructions.

---

## 📋 Manual Setup (If you want separate files)

---

## Step 1: Download VEXcode V5

1. Go to: **https://codev5.vex.com/**
2. Download for your OS (Mac/Windows/Chrome OS)
3. Install VEXcode V5
4. Open VEXcode V5

---

## Step 2: Create New C++ Project

1. In VEXcode V5: **File → New Project**
2. Select: **"V5 Brain"**
3. Choose: **"C++"** as programming language
4. Name it: **"vex-iq"** (or any name)
5. Click **"Create"**

You'll see:
- A `main.cpp` file (empty or template)
- A `main.h` file (with VEX includes)

---

## Step 3: Copy Your Code

### Option A: Keep Controller Structure (Recommended)

1. **In VEXcode project root**, create a folder called `controllers`
   - Right-click in file explorer → New Folder → Name it "controllers"

2. **Copy these files from your project**:
   ```
   From: /Users/johnnywinn/src/vex-iq/src/controllers/
   To:   VEXcode project root/controllers/
   
   - DriveTrain.cpp
   - DriveTrain.h
   - IntakeController.cpp
   - IntakeController.h
   - RampController.cpp
   - RampController.h
   - PneumaticController.cpp
   - PneumaticController.h
   ```

3. **Copy main files**:
   ```
   From: /Users/johnnywinn/src/vex-iq/src/main.cpp
   To:   VEXcode project root/main.cpp
   
   (Replace the existing main.cpp)
   
   From: /Users/johnnywinn/src/vex-iq/src/main.h
   To:   VEXcode project root/main.h
   ```

4. **Your includes should work as-is**:
   ```cpp
   #include "controllers/DriveTrain.h"  // ✅ Should work!
   ```

### Option B: Flat Structure (Simpler, but less organized)

1. **Copy ALL files** (both .cpp and .h) to VEXcode project root:
   ```
   Copy from src/controllers/* to VEXcode root/
   Copy from src/main.* to VEXcode root/
   ```

2. **Update includes in main.cpp**:
   ```cpp
   // Change from:
   #include "controllers/DriveTrain.h"
   
   // To:
   #include "DriveTrain.h"
   ```

   (Do this for all controller includes)

---

## Step 4: Verify File Structure

Your VEXcode project should look like:

**Option A** (Recommended):
```
vex-iq-project/
├── main.cpp
├── main.h
└── controllers/
    ├── DriveTrain.cpp
    ├── DriveTrain.h
    ├── IntakeController.cpp
    ├── IntakeController.h
    ├── RampController.cpp
    ├── RampController.h
    ├── PneumaticController.cpp
    └── PneumaticController.h
```

**Option B** (Flat):
```
vex-iq-project/
├── main.cpp
├── main.h
├── DriveTrain.cpp
├── DriveTrain.h
├── IntakeController.cpp
├── IntakeController.h
├── RampController.cpp
├── RampController.h
├── PneumaticController.cpp
└── PneumaticController.h
```

---

## Step 5: Build Project

1. **Click "Build" button** in VEXcode (or File → Build)
2. **Check output panel** for any errors
3. If there are errors:
   - Check include paths match file locations
   - Verify all files are in the project

---

## Step 6: Connect Robot and Upload

1. **Connect V5 Brain** to computer via USB cable
2. **Power on** the V5 Brain
3. **Wait** for VEXcode to detect the Brain (shows in status bar)
4. **Click "Download" button** (or File → Download)
5. **Wait** for upload to complete
6. **Check Brain screen** - should show your program name

---

## Step 7: Test on Robot

1. **Enable Driver Control mode** (or Autonomous)
2. **Test controller buttons**:
   - Sticks → Drive train
   - R1/R2 → Intake
   - L1/L2 → Ramp (first two wheels)
   - X/Y → Full power ramp
   - A → Toggle pneumatic height

---

## Troubleshooting VEXcode

### Build Errors - Include Not Found

**If using controllers/ folder**:
```cpp
#include "controllers/DriveTrain.h"  // ✅ Should work
```

**If using flat structure**:
```cpp
#include "DriveTrain.h"  // ✅ Should work
```

### Build Errors - Multiple Definitions

- Make sure each `.cpp` file is included in project exactly once
- Check for duplicate files

### Upload Fails - Device Not Found

- Check USB connection
- Power on the Brain
- Try different USB port
- Restart VEXcode
- Unplug and replug USB

### Robot Doesn't Respond

- Check port numbers in `main.cpp` match robot wiring
- Verify motors are plugged in
- Check motor reversal flags
- Test with simple motor spin command first

---

## Advantages of VEXcode V5

✅ **Official VEX tool** - Supported by VEX  
✅ **Easy to use** - Visual interface, no command line  
✅ **Automatic compilation** - Handles build process  
✅ **Built-in terminal** - For debugging output  
✅ **Reliable upload** - Works consistently  
✅ **Cross-platform** - Mac, Windows, Chrome OS  

---

## Development Workflow

You can use **both** systems:

1. **Development** (local):
   ```bash
   make test  # Run unit tests locally
   ```

2. **Deployment** (VEXcode):
   - Copy files to VEXcode project
   - Build and upload to robot
   - Test on hardware

This gives you:
- ✅ Fast local testing (unit tests)
- ✅ Easy robot deployment (VEXcode)

---

## Quick Checklist

- [ ] VEXcode V5 installed
- [ ] New C++ project created
- [ ] Files copied to project
- [ ] Includes updated (if needed)
- [ ] Project builds successfully
- [ ] Robot connected via USB
- [ ] Code uploaded to robot
- [ ] Robot tested successfully

---

**VEXcode V5 is much easier than PROS for most users!** Give it a try.

Need help with any step? Let me know!

