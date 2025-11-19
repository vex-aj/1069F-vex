# Deployment Options for VEX V5 Robot

## Overview

If PROS isn't working, here are several alternative ways to deploy your code to the VEX V5 Brain:

---

## Option 1: VEXcode V5 IDE (Recommended - Easiest)

**Best for**: Quick deployment, official VEX tool, visual interface

### Steps:

1. **Download VEXcode V5**
   - Go to: [codev5.vex.com](https://codev5.vex.com/)
   - Download for your OS (Mac/Windows/Chrome OS)
   - Install and open

2. **Create New C++ Project**
   - File → New Project
   - Choose "V5 Brain"
   - Select "C++" as programming language
   - Name it (e.g., "vex-iq")

3. **Copy Your Code**
   
   **Option A: Copy main.cpp directly**
   - Open `src/main.cpp` from your project
   - Copy all content
   - Paste into VEXcode's main.cpp
   
   **Option B: Import controller files**
   - In VEXcode project, create a folder called "controllers"
   - Copy all files from `src/controllers/` to this folder:
     - DriveTrain.cpp, DriveTrain.h
     - IntakeController.cpp, IntakeController.h
     - RampController.cpp, RampController.h
     - PneumaticController.cpp, PneumaticController.h
   - Copy `src/main.cpp` and `src/main.h` to VEXcode's root
   - Update include paths in main.cpp if needed:
     ```cpp
     #include "controllers/DriveTrain.h"  // Should work if in controllers folder
     ```

4. **Update Include Paths** (if needed)
   
   If VEXcode doesn't find headers, try:
   ```cpp
   #include "DriveTrain.h"  // Instead of "controllers/DriveTrain.h"
   ```
   Then add `controllers` folder files to the same directory as main.cpp

5. **Build and Download**
   - Connect V5 Brain via USB
   - Power on the Brain
   - Click "Build" button (should compile successfully)
   - Click "Download" button (uploads to robot)

### Advantages:
- ✅ Official VEX tool
- ✅ Easy to use visual interface
- ✅ Handles all compilation automatically
- ✅ Built-in terminal/debugging
- ✅ Works on Mac, Windows, Chrome OS

### Disadvantages:
- ⚠️ Requires separate VEXcode installation
- ⚠️ File structure slightly different from PROS

---

## Option 2: VEXcode V5 Web Version

**Best for**: No installation needed, works in browser

### Steps:

1. **Open VEXcode V5 Web**
   - Go to: [codev5.vex.com](https://codev5.vex.com/) in browser
   - Works in Chrome/Edge (best compatibility)

2. **Create New C++ Project**
   - Similar to desktop version
   - Create project → C++ → V5 Brain

3. **Copy Code Files**
   - Same as Option 1
   - Copy main.cpp and controller files

4. **Build and Download**
   - Same process as desktop version

### Advantages:
- ✅ No installation needed
- ✅ Works anywhere with internet
- ✅ Same features as desktop version

### Disadvantages:
- ⚠️ Requires internet connection
- ⚠️ Slightly slower than desktop version
- ⚠️ File management in browser

---

## Option 3: Manual File Transfer (Simplest Structure)

**Best for**: Minimal setup, single file approach

### Steps:

1. **Create Single File Version**
   - Combine main.cpp with all controller code
   - Or keep separate files but flatten structure

2. **Copy to VEXcode**
   - Create new C++ project in VEXcode
   - Copy everything into one directory
   - Update includes to match flat structure

3. **Build and Download**
   - Use VEXcode's build/download buttons

---

## Option 4: Use Existing Makefile + Manual Copy

**Best for**: If you want to keep local testing but deploy via VEXcode

### Steps:

1. **Keep Current Setup**
   - Your Makefile works for local testing: `make test`
   - Keep this for development

2. **Use VEXcode for Deployment**
   - Create VEXcode project
   - Copy files when ready to deploy
   - Build and upload via VEXcode

3. **Development Workflow**
   - Develop locally using `make test`
   - When ready, copy to VEXcode
   - Deploy to robot

---

## Quick Comparison

| Option | Difficulty | Setup Time | Best For |
|--------|-----------|------------|----------|
| **VEXcode V5 IDE** | Easy | 5 min | Most users |
| **VEXcode V5 Web** | Easy | 5 min | No installation |
| **Manual File Copy** | Medium | 10 min | Simple structure |
| **PROS** | Hard | 30+ min | Advanced users |

---

## Recommendation: VEXcode V5 IDE

For your situation, **VEXcode V5 IDE** is the best option:
1. ✅ Official VEX tool
2. ✅ Easy setup
3. ✅ Reliable compilation
4. ✅ Simple upload process
5. ✅ Works with your existing code structure

---

## Next Steps for VEXcode

1. **Download VEXcode V5** from codev5.vex.com
2. **Create new C++ project**
3. **Copy your files**:
   - `src/main.cpp` → main.cpp in VEXcode
   - `src/main.h` → main.h in VEXcode
   - Create "controllers" folder
   - Copy all `src/controllers/*` files to it
4. **Update includes** (if needed):
   ```cpp
   #include "controllers/DriveTrain.h"
   ```
5. **Build and Download**

Your code should work in VEXcode with minimal changes! The controller classes are already compatible with VEXcode since they use standard C++ and VEX library calls.

---

## Troubleshooting VEXcode

### Include Path Errors
- Make sure controller files are in same directory as main.cpp OR
- Create "controllers" folder and use `#include "controllers/DriveTrain.h"`

### Compilation Errors
- Check that all `.cpp` files are included in project
- Verify `vex.h` is accessible (should be automatic in VEXcode)

### Upload Fails
- Check USB connection
- Power on the Brain
- Try different USB port
- Restart VEXcode

---

Need help setting up any of these options? Let me know which one you'd like to try!

