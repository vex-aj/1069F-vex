# VEX V5 Robot - Test-Driven Development Project

A VEX V5 robotics project demonstrating Test-Driven Development (TDD) best practices with C++.

## Project Structure

See [docs/PROJECT_STRUCTURE.md](docs/PROJECT_STRUCTURE.md) for complete details.

Key directories:
- `src/` - Modular source code (controller classes)
- `tests/` - Unit tests
- `vexcode_single_file/` - Single-file version for VEXcode deployment
- `docs/` - Documentation

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

For VEX V5 deployment, see deployment guides:
- **[VEXcode Setup](docs/VEXCODE_SETUP.md)** - Recommended: Use VEXcode V5 IDE
- **[Deployment Options](docs/DEPLOYMENT_OPTIONS.md)** - All deployment methods
- Single-file version ready in `vexcode_single_file/main.cpp`

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

## Documentation

- **[TDD Guide](docs/TDD_GUIDE.md)** - Comprehensive TDD guide for robotics
- **[Contributing](CONTRIBUTING.md)** - Development workflow and guidelines
- **[Project Structure](docs/PROJECT_STRUCTURE.md)** - Directory organization
- **[Style Guidelines](docs/AGENT.md)** - C++ coding standards
- **[Deployment Guide](docs/VEXCODE_SETUP.md)** - How to deploy to robot

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md) for the development workflow:
1. Write tests first (TDD)
2. Implement feature
3. Update single-file version
4. Commit

Happy coding! 🤖

