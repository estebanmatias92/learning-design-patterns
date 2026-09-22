# Visitor — C++ playground (Pitchfork layout, C++17)

Isolated env for trying Visitor-pattern examples. Reproducible with any
recent GCC/Clang/MSVC + CMake + Make.

## Requirements

| Tool | Minimum | Tested locally |
| ---- | ------- | -------------- |
| C++ compiler (GCC / Clang / MSVC) | GCC 7 / Clang 5 / MSVC 2017 15.7 (C++17) | GCC 16, Clang 22 |
| CMake | 3.16 | 4.4 |
| GNU Make | 3.81 | 4.4 |

No external dependencies (no Conan/vcpkg, no test framework yet).

## Quickstart

```sh
make build
make run EXAMPLE=<name>   # e.g. make run EXAMPLE=basic_shapes
make clean
```

Available demos: `basic_shapes`, `banking`, `document`.

Pure CMake (no Makefile):

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

## Layout (Pitchfork, merged headers)

```
code/
  CMakeLists.txt
  Makefile            # thin wrapper, delegates to CMake
  README.md
  .gitignore
  .clang-format
  src/                # merged headers+sources, namespaced subdirs
  examples/           # one dir + one binary per demo: <name>/main.cpp
  tests/              # reserved (.gitkeep), builds only with -DVISITOR_BUILD_TESTS=ON
  build/              # ephemeral, never committed
```

Omitted on purpose (unused): `include/`, `libs/`, `extras/`, `external/`,
`data/`, `docs/`, `tools/`, `cmake/`.

## Add a new demo

1. Create `examples/<name>/main.cpp`.
2. Register it in `examples/CMakeLists.txt`:
   `add_executable(<name> <name>/main.cpp)`
3. `make build && make run EXAMPLE=<name>`

Library components (when they exist) go in `src/` mirroring the namespace,
e.g. `visitor::shapes::circle` → `src/visitor/shapes/circle.hpp` +
`src/visitor/shapes/circle.cpp`. Never place sources at the root of `src/`.

## Build options

- `VISITOR_BUILD_EXAMPLES` (default ON): set `-DVISITOR_BUILD_EXAMPLES=OFF`
  to skip `examples/`.
- `VISITOR_BUILD_TESTS` (default OFF): reserved until a framework is wired up.
