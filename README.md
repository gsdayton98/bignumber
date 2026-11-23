# BigNumber

My implementation of an extended precision library.

Intent is to be as simple as possible but no simpler. Functions that can
generate an error return a std::optional<> instead. Constructors are private,
and only perform structure like initialization. Constructions that can produce
an error use a generator function that returns a std::expected<> instead.



