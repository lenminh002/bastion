# Bastion

A terminal tower defense project for learning data structures in C++.

## Build And Run

From the project root:

```bash
make
```

This configures CMake, builds the game, and runs:

```bash
./build/bastion
```

Useful shortcuts:

```bash
make build      # configure and build all targets
make test       # build and run tests
make configure  # configure CMake only
make clean      # clean generated build outputs
```

The `Makefile` is only a shortcut wrapper. CMake is still the real build system.

Raw CMake commands:

```bash
cmake -S . -B build
cmake --build build
./build/bastion
```

After the first CMake configure, most code changes only need:

```bash
cmake --build build
./build/bastion
```

Run this again only when CMake setup changes, such as adding new source files:

```bash
cmake -S . -B build
```

Run ArrayList tests directly:

```bash
cmake --build build --target array_list_tests
./build/array_list_tests
```

## Project Layout

```text
include/        Header files
src/            C++ implementation files
tests/          Future tests
docs/           Docs
build/          Generated build output, not committed
```