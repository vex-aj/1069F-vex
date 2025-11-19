# Contributing

## Development Workflow

This project uses **Test-Driven Development (TDD)** to ensure code quality and maintainability.

### Standard Development Process

1. **Write Tests First** (RED)
   - Create or update test file in `tests/`
   - Write tests for new feature/change
   - Run `make test` - tests should fail ❌

2. **Implement Feature** (GREEN)
   - Write minimal code in `src/controllers/` to make tests pass
   - Run `make test` - all tests should pass ✅

3. **Refactor** (REFACTOR)
   - Improve code while keeping tests passing
   - Run `make test` after each change ✅

4. **Update Single-File Version** (for deployment)
   - After tests pass, update `vexcode_single_file/main.cpp`
   - Copy controller class implementations inline
   - Test that single-file version compiles in VEXcode

5. **Commit**
   - All tests passing
   - Single-file version updated
   - Code follows style guidelines

## Development Principles

- **Test First**: Always write tests before implementation
- **Keep Tests Passing**: Never commit with failing tests
- **Separate Logic from Hardware**: Pure functions in controllers, hardware in main.cpp
- **Update Both Versions**: Maintain both modular (`src/`) and single-file (`vexcode_single_file/`) versions

## Quick Reference

```bash
# Run all tests
make test

# Clean build artifacts
make clean

# Test single-file version
# Open vexcode_single_file/main.cpp in VEXcode and build
```

## Documentation

- **[TDD Guide](docs/TDD_GUIDE.md)** - Comprehensive guide on Test-Driven Development practices
- **[Project Structure](docs/PROJECT_STRUCTURE.md)** - Directory organization and file layout
- **[Style Guidelines](docs/AGENT.md)** - C++ coding standards and VEX-specific patterns
- **[Features](docs/features.md)** - Feature breakdown and requirements
- **[Deployment Guide](docs/VEXCODE_SETUP.md)** - How to deploy code to VEX V5 Brain

## Questions?

- Check the documentation in `docs/` directory
- Review existing code and tests for patterns
- Follow the TDD workflow described above

Happy coding! 🤖

