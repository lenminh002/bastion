# Bastion

A terminal tower defense project for learning data structures in C++.

## Build And Run

From the project root:

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

## Project Layout

```text
include/        Header files
src/            C++ implementation files
tests/          Future tests
docs/lessons/   Lesson notes
build/          Generated build output, not committed
```
