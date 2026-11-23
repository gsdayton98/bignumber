# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

@AGENTS.md

## Working agreement (Claude Code)

- The working agreement in `AGENTS.md` applies. In addition, never commit on `main`; if the current branch is `main`,
  only suggest a commit message. A request not to commit always wins.
- Add the trailer `Co-Authored-By: Claude <noreply@anthropic.com>` to every commit message.

## Build directory (Claude Code)

Use `../build/bignumber/claude` as the `<agent>` build directory from `AGENTS.md`:

```bash
cmake -B ../build/bignumber/claude -S .
cmake --build ../build/bignumber/claude
ctest --test-dir ../build/bignumber/claude
```
