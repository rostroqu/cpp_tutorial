# CLAUDE.md

## Project

A personal C++ course. The author comes from full-stack work (TypeScript, Java,
Python, C#) plus a year of C, and is learning C++ here on the way to ESP32 /
ESP-IDF firmware. Pitch explanations at "experienced developer, new language":
explain what has no equivalent in managed languages (const-correctness, value
vs. reference semantics, move, RAII, ownership); don't re-explain programming.

Each `lesson_N/` directory is one exercise and becomes its own executable
target automatically — `CMakeLists.txt` globs `lesson_*` with
`CONFIGURE_DEPENDS`, so never add lessons there by hand.

**The author writes the lesson code themselves.** Do not fix warnings or
refactor lessons unless asked; point them out and explain them instead.

## Build & run

```bash
cmake -S . -B build/debug -G Ninja -DCMAKE_BUILD_TYPE=Debug   # once
cmake --build build/debug --target lesson_2 && ./build/debug/lesson_2
```

Editor shortcuts (file inside the lesson must be open): `Ctrl+X Ctrl+S` save +
build, `Ctrl+Shift+B` build, `F5` gdb, `Ctrl+Shift+P` → Run Task → run /
clang-tidy / cppcheck / clang-format / valgrind.

- Standard is **C++20** (`CMakeLists.txt`, `.vscode/*.json` all agree). Keep
  them in sync. GCC 13 has no `<print>`, so no C++23.
- `build/debug/` has ASan + UBSan + `_GLIBCXX_ASSERTIONS` baked in. Valgrind
  uses the separate `build/valgrind/` (sanitizers off — they cannot coexist).
- Toolchain: WSL2, GCC 13, clang-tidy/clang-format 18, cppcheck 2.13,
  valgrind 3.22, gdb 15. **No clang/clangd.**

## Analysis stack — gotchas that cost time to rediscover

- `.clang-tidy` carries `ExtraArgs: ["-Wshadow-all"]`. It is clang-only; GCC
  rejects it, so it must never move into `CMakeLists.txt`. It exists because
  clang's `-Wshadow` misses constructor-parameter-shadows-field, which GCC's
  catches.
- `.vscode/settings.json` pins `clangTidy.path` to `/usr/bin/clang-tidy`.
  cpptools' bundled `LLVM/bin/clang-tidy` ships no resource headers and fails
  every file with `'stddef.h' file not found`. Don't remove the pin.
- `readability-make-member-function-const` does not fire on getters defined
  inline in a class. Missing `const` on member functions must be caught by eye.
- New lesson files are absent from `compile_commands.json` until built once;
  IntelliSense squiggles are unreliable until then.

## Editor environment
`emacs-mcx` is active: **`Ctrl+S` is isearch-forward, not save.** Save is
`Ctrl+X Ctrl+S`. Never bind anything to `Ctrl+S`.

## Roadmap (not started)

Native ESP-IDF v6.x in WSL (not PlatformIO), `usbipd-win` for flashing, logic
in `components/` so it is host-testable with GoogleTest + CTest, then GitHub
Actions: lint → host tests (sanitizers on) → `esp-idf-ci-action` → QEMU.

---

# Behavioral guidelines

Behavioral guidelines to reduce common LLM coding mistakes. Merge with project-specific instructions as needed.

**Tradeoff:** These guidelines bias toward caution over speed. For trivial tasks, use judgment.

## 1. Think Before Coding

**Don't assume. Don't hide confusion. Surface tradeoffs.**

Before implementing:
- State your assumptions explicitly. If uncertain, ask.
- If multiple interpretations exist, present them - don't pick silently.
- If a simpler approach exists, say so. Push back when warranted.
- If something is unclear, stop. Name what's confusing. Ask.

## 2. Simplicity First

**Minimum code that solves the problem. Nothing speculative.**

- No features beyond what was asked.
- No abstractions for single-use code.
- No "flexibility" or "configurability" that wasn't requested.
- No error handling for impossible scenarios.
- If you write 200 lines and it could be 50, rewrite it.

Ask yourself: "Would a senior engineer say this is overcomplicated?" If yes, simplify.

## 3. Surgical Changes

**Touch only what you must. Clean up only your own mess.**

When editing existing code:
- Don't "improve" adjacent code, comments, or formatting.
- Don't refactor things that aren't broken.
- Match existing style, even if you'd do it differently.
- If you notice unrelated dead code, mention it - don't delete it.

When your changes create orphans:
- Remove imports/variables/functions that YOUR changes made unused.
- Don't remove pre-existing dead code unless asked.

The test: Every changed line should trace directly to the user's request.

## 4. Goal-Driven Execution

**Define success criteria. Loop until verified.**

Transform tasks into verifiable goals:
- "Add validation" → "Write tests for invalid inputs, then make them pass"
- "Fix the bug" → "Write a test that reproduces it, then make it pass"
- "Refactor X" → "Ensure tests pass before and after"

For multi-step tasks, state a brief plan:
```
1. [Step] → verify: [check]
2. [Step] → verify: [check]
3. [Step] → verify: [check]
```

Strong success criteria let you loop independently. Weak criteria ("make it work") require constant clarification.

---

**These guidelines are working if:** fewer unnecessary changes in diffs, fewer rewrites due to overcomplication, and clarifying questions come before implementation rather than after mistakes.
