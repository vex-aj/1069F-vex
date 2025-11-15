# VEX V5 Robot - Test-Driven Development Project

A VEX V5 robotics project demonstrating Test-Driven Development (TDD) best practices with C++.

## Project Structure

```
vex-iq/
├── main.cpp              # Robot code (hardware integration)
├── main.h                # VEX header file
├── DriveTrain.h          # Drive train logic (testable)
├── DriveTrain.cpp        # Drive train implementation
├── tests/
│   └── test_drivetrain.cpp  # Unit tests for DriveTrain
├── TDD_GUIDE.md          # Comprehensive TDD guide
├── Makefile              # Build system
└── README.md             # This file
```

## Quick Start

### Running Tests

```bash
# Build and run all tests
make test

# Or manually
g++ -std=c++17 tests/test_drivetrain.cpp DriveTrain.cpp -o test_runner
./test_runner
```

### Building Robot Code

For actual VEX V5 deployment, you'll need the PROS toolchain:
- Download PROS CLI from [pros.cs.purdue.edu](https://pros.cs.purdue.edu/)
- Use `pros make` or `pros upload` commands

## TDD Workflow

1. **RED**: Write a test (it will fail)
2. **GREEN**: Write minimal code to make it pass
3. **REFACTOR**: Improve code while keeping tests passing

See `TDD_GUIDE.md` for detailed best practices!

## Key Features

- ✅ **Testable Architecture**: Logic separated from hardware
- ✅ **Unit Tests**: Test drive train calculations without motors
- ✅ **Deadband**: Prevents controller drift
- ✅ **Tank Drive**: Left/right independent control
- ✅ **Arcade Drive**: Forward/turn control (commented, easy to enable)

## Architecture

### Separation of Concerns

```
Hardware Layer (main.cpp)
    ↓ calls
Logic Layer (DriveTrain.cpp)  ← Testable!
    ↑ tested by
Test Layer (tests/test_drivetrain.cpp)
```

This separation allows us to:
- Test logic without hardware
- Run tests quickly (no motors needed)
- Verify behavior before deploying to robot

## Best Practices Demonstrated

1. **Pure Functions**: DriveTrain methods have no side effects
2. **Independent Tests**: Each test can run alone
3. **Edge Case Testing**: Boundary conditions covered
4. **Clear Names**: Tests describe what they verify
5. **Fast Tests**: Complete suite runs in seconds

## Learning Resources

- `TDD_GUIDE.md` - Comprehensive TDD guide for robotics
- Inline comments explain each section
- Test examples show proper TDD patterns

## Next Steps

1. Run the tests: `make test`
2. Add a new feature using TDD:
   - Write test first
   - Implement feature
   - Refactor
3. Deploy to robot and test with hardware

Happy coding! 🤖

