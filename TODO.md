# TODO

## Open work

- Extend the `Array` tests in `test/test_array.cpp` (Boost.Test, target `test_bignumber`). Only `test_create` exists;
  cover move construction and move assignment, a zero capacity, and the `Error::bad_allocation` path.
- `CMakePresets.json`: the `benchmark` and `docs` presets set `BIGNUMBER_BENCHMARKS` and `BIGNUMBER_DOCS`, and the
  `docs` build preset builds a `docs` target; `CMakeLists.txt` defines none of them. Add them or drop the presets.
- Create `.git-blame-ignore-revs` if the LF-normalization commit should be ignored by `git blame`.

## Decisions

- Namespace: the CMake export namespace is `bignumber::` (target `bignumber::bignumber`, matching the package name), and
  the C++ namespace is `big_number`.
- Errors: functions that can fail return `std::optional<>`. Constructors are private and only initialize the structure.
  A construction that can fail goes through a factory function that returns `std::expected<>` (`README.md`).
- `Array::create` returns `std::expected<Array, Error>`, where `big_number::Error` is an enum (`bad_allocation`); this
  replaces `std::exception`, which sliced derived exceptions. Copy is deleted; move is supported.
