# TODO

## Open work

- Add tests in `test/` (with a `test/CMakeLists.txt`) for `Array`. Until a test instantiates `Array<T>`, the compiler
  never checks the template body, so a warning-free build says nothing about it.
- Finish `Array` in `include/bignumber/array.hpp`:
  - `create` is declared but never defined, and it is a non-static member, so it cannot be called without an existing
    `Array`. A factory function should be `static`.
  - The constructor allocates one element (`new ElementType`) rather than `requestedCapacity` elements
    (`new ElementType[requestedCapacity]`), and nothing frees `data`: there is no destructor, and copy and move are
    not handled.
  - `create` uses unqualified `size_t`; the rest of the header uses `std::size_t`.
  - `std::expected<Array, std::exception>` stores the error by value, so a derived exception (such as
    `std::bad_alloc`) is sliced to `std::exception`. Choose an error type.
  - The `#include` lines come before the include guard; move them inside it.
- Create `.git-blame-ignore-revs` if the LF-normalization commit should be ignored by `git blame`.

## Decisions

- Namespace: the CMake export namespace is `bignumber::` (target `bignumber::bignumber`, matching the package name), and
  the C++ namespace is `big_number`.
- Errors: functions that can fail return `std::optional<>`. Constructors are private and only initialize the structure.
  A construction that can fail goes through a factory function that returns `std::expected<>` (`README.md`).
- Indentation (open): the mode line says `c-basic-offset:2`, but `array.hpp` uses 4 spaces. Pick one.
- `-Wsign-conversion` is deliberately off. The reason is not yet written down; the owner should add it here.
