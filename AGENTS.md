Copyright notices in source files are repository requirements. Preserve them verbatim and do not flag, critique, or suggest removing them during review.

Each new source file starts with the same two header lines as existing files (mode line and copyright line), each followed by a newline.

## Overview

Personal implementation of an extended precision library.
Open work is tracked in `TODO.md`.

## Working agreement

- Commit only documentation files (`AGENTS.md`, `CLAUDE.md`, `TODO.md`). Leave every other change in the working tree for the owner to review, and suggest a commit message instead.
- Do not commit a code change together with a TODO change: commit the TODO file by itself (`git commit <file>`).

## Build System (C++)

The project uses CMake with C++23 and builds a shared library, `bignumber`.

Do not build in the source tree. Agents use the out-of-tree build directory `../build/bignumber/agent`. CLion uses its own
`cmake-build-*` profile directories; do not use those for agent builds.

```bash
# Configure (from repo root)
cmake -B ../build/bignumber/agent -S .

# Build all
cmake --build ../build/bignumber/agent

# Run all tests
ctest --test-dir ../build/bignumber/agent
```

### Tests

Tests live in `test/` and use Boost.Test (`find_package(Boost REQUIRED CONFIG COMPONENTS unit_test_framework)`, linked
dynamically). The root `CMakeLists.txt` calls `include(CTest)` and adds `test/` when `BUILD_TESTING` is on and
`test/CMakeLists.txt` exists. All test sources build into one executable, `test_bignumber`, registered with CTest under
the same name:

- `test/test.cpp` defines `BOOST_TEST_MAIN` and `BOOST_TEST_DYN_LINK`; do not put test cases there.
- `test/test_array.cpp` holds the `Array` tests (suite `TestBigNumber`).
- Add each new test file to `add_executable(test_bignumber ...)` in `test/CMakeLists.txt`.

### Presets

`CMakePresets.json` defines configure, build and test presets `debug`, `release`, `asan` and `werror`. Their build
directories are `../build/bignumber/presets/<preset>`, so they are also out of tree:

```bash
cmake --preset werror
cmake --build --preset werror
ctest --preset werror
```

The `benchmark` and `docs` presets refer to options and a target that `CMakeLists.txt` does not define yet (see
`TODO.md`); do not use them.

### Warnings

The root `CMakeLists.txt` compiles with `-Wall -Wextra -Wshadow -Wconversion -Wno-sign-conversion` (option
`BIGNUMBER_WARNINGS`, on by default; Clang and GCC). Keep the build warning-free: a new warning means new code to fix.
`-Wsign-conversion` is deliberately off; see Decisions in `TODO.md`.

`BIGNUMBER_WERROR` (default OFF) adds `-Werror`. `BIGNUMBER_SANITIZERS` is a semicolon-separated list for
`-fsanitize=` (for example `address;undefined`); the `werror` and `asan` presets in `CMakePresets.json` set them.

Warnings come from `add_compile_options` only. Do not also pass `BIGNUMBER_WARNINGS` to `target_compile_options`; it
expands to `ON` and breaks the compile command.

### Install layout

The root `CMakeLists.txt` defaults `CMAKE_INSTALL_PREFIX` to `$HOME`. `cmake --install <build-dir>` puts:

- the shared library in `${CMAKE_INSTALL_LIBDIR}` (`~/lib/libbignumber.dylib`)
- the headers in `${CMAKE_INSTALL_INCLUDEDIR}/bignumber` (`~/include/bignumber/`), including the generated `bignumber_export.h`
- the CMake package in `~/lib/cmake/bignumber`, exported with namespace `bignumber::` (link `bignumber::bignumber`):
  `bignumber.cmake` (the exported targets), `bignumber-config.cmake` (generated from `cmake/bignumber-config.cmake.in`)
  and `bignumber-config-version.cmake` (`AnyNewerVersion`), so a consumer uses `find_package(bignumber CONFIG)`

The install keeps each file's modification time, so a re-installed but unchanged file (such as the generated
`bignumber_export.h`) shows its old timestamp. `CMakeLists.txt` also includes CPack for packaging.

The CMake namespace `bignumber::` names the package; the C++ namespace is `big_number`.

## Layout and style

- Public headers go in `include/bignumber/*.hpp`, sources in `src/*.cpp`. Every new file must be added to `add_library` in `CMakeLists.txt`, and public headers to `HEADERS`.
- Mark exported symbols with `BIGNUMBER_API`; visibility is hidden by default (`-fvisibility=hidden`).
- Error handling (see `README.md`): functions that can fail return `std::optional<>`. Constructors are private and only
  initialize the structure; a construction that can fail goes through a factory function that returns `std::expected<>`.
- Indentation: the mode line says `c-basic-offset:2`, but `array.hpp` uses 4 spaces. The rule is an open decision in `TODO.md`.

## Repository conventions

- **File names:** all lowercase, with snake_case between words (`array.hpp`). A Mac working tree is case-preserving but
  case-insensitive, so names that differ only in case collide there. Class names start with a capital and use CamelCase
  (`Array`). Tools that dictate a name keep it (`README.md`, `CMakeLists.txt`, `AGENTS.md`, `CLAUDE.md`). A case-only
  rename needs `git mv` through a temporary name on the Mac.
- **Namespace:** C++ code lives in namespace `big_number`.
- **Line endings:** every text file is LF. `.gitattributes` (`* text=auto eol=lf`) enforces it and converts CRLF on
  commit.