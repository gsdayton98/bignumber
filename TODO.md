# TODO

## Open work

- Extend the `Array` tests in `test/test_array.cpp` (Boost.Test, target `test_bignumber`). Only `test_create` exists;
  cover move construction and move assignment, a zero capacity, and the `Error::bad_allocation` path.
- `test/test_array.cpp`: `BOOST_CHECK_EQUAL(array.size(), 0)` compares `std::size_t` with `int` and raises
  `-Wsign-compare` inside Boost; compare with `0U`. It also uses unqualified `size_t` and `std::move` without
  `<utility>`.
- `include/bignumber/array.hpp`: `capacity()` and `size()` return unqualified `size_t`; use `std::size_t`.
- `CMakeLists.txt`: `$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/include` puts `/include` outside the generator
  expression, so the installed `bignumber::bignumber` exports the include directory `/include`. Use
  `$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>`.
- `CMakePresets.json`: the `benchmark` and `docs` presets set `BIGNUMBER_BENCHMARKS` and `BIGNUMBER_DOCS`, and the
  `docs` build preset builds a `docs` target; `CMakeLists.txt` defines none of them. Add them or drop the presets.
- `AGENTS.md` still says "No tests exist yet"; describe `test/`, the Boost.Test dependency and the presets.
- Create `.git-blame-ignore-revs` if the LF-normalization commit should be ignored by `git blame`.

## Decisions

- Namespace: the CMake export namespace is `bignumber::` (target `bignumber::bignumber`, matching the package name), and
  the C++ namespace is `big_number`.
- Errors: functions that can fail return `std::optional<>`. Constructors are private and only initialize the structure.
  A construction that can fail goes through a factory function that returns `std::expected<>` (`README.md`).
- Indentation (open): the mode line says `c-basic-offset:2`, but `array.hpp` uses 4 spaces. Pick one.
- `Array::create` returns `std::expected<Array, Error>`, where `big_number::Error` is an enum (`bad_allocation`); this
  replaces `std::exception`, which sliced derived exceptions. Copy is deleted; move is supported.
- `-Wsign-conversion` is deliberately off. The reason is not yet written down; the owner should add it here.
