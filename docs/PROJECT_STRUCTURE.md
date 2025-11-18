# Project Structure

## Directory Organization

```
vex-iq/
├── src/                              # Source code
│   ├── main.cpp, main.h             # Robot main code (hardware integration)
│   └── controllers/                  # Controller classes (testable logic)
│       ├── DriveTrain.cpp, DriveTrain.h
│       ├── IntakeController.cpp, IntakeController.h
│       ├── RampController.cpp, RampController.h
│       └── PneumaticController.cpp, PneumaticController.h
│
├── tests/                            # Unit tests
│   ├── test_drivetrain.cpp
│   ├── test_intakecontroller.cpp
│   ├── test_rampcontroller.cpp
│   └── test_pneumaticcontroller.cpp
│
├── docs/                             # Documentation
│   ├── AGENT.md                     # C++ style guidelines
│   ├── DEPLOYMENT_CHECKLIST.md      # Deployment guide
│   ├── PROJECT_SUMMARY.md           # Project overview
│   ├── PROJECT_STRUCTURE.md         # This file
│   ├── README.md                    # Quick start guide
│   ├── TDD_GUIDE.md                 # TDD best practices
│   └── features.md                  # Feature breakdown
│
├── build/                            # Build artifacts (gitignored)
├── Makefile                          # Build system
└── .gitignore                        # Git ignore rules
```

## Organization Principles

### 1. **src/** - Source Code
- **main.cpp, main.h**: Hardware integration layer
  - Motor declarations
  - Controller setup
  - Competition mode
  - Calls controller classes for logic

- **src/controllers/**: Testable logic layer
  - Pure functions (no hardware dependencies)
  - All controller classes grouped together
  - Easy to find and maintain

### 2. **tests/** - Unit Tests
- One test file per controller class
- Tests are independent and fast
- Can run without hardware

### 3. **docs/** - Documentation
- All markdown documentation in one place
- Easy to find project information
- Includes guides, checklists, and summaries

### 4. **build/** - Build Artifacts
- Compiled test runners
- Object files
- Gitignored (not committed)

## Benefits

✅ **Clear Separation**: Source, tests, docs, and build artifacts are separated  
✅ **Easy Navigation**: Related files are grouped together  
✅ **Scalable**: Easy to add new controllers or features  
✅ **Professional**: Follows common C++ project structure  
✅ **Maintainable**: Easy to find and modify code

## Include Paths

### From main.cpp:
```cpp
#include "controllers/DriveTrain.h"
```

### From test files:
```cpp
#include "../src/controllers/DriveTrain.h"
```

### Makefile:
- Uses `-Isrc` flag to include src directory
- All paths updated to reflect new structure

## Running Tests

```bash
make test    # Runs all tests (52 total)
make clean   # Cleans build artifacts
```

All tests pass with the new structure! ✅

