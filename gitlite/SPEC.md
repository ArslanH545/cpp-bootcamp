# Git-Lite — Spec

Three stages, one program, one menu.

- **Stage 1 (M1–M10): build the engine yourself.** A console version-control tool for ONE text file. Own linked list, undo stack, LCS diff, on-disk snapshots. Never touches real git.
- **Stage 2 (M11–M13): swap the engine for real git.** Same menu; behind it every item runs the real `git` binary via `fork`/`execvp`/pipes (no shell).
- **Stage 3 (S1–S4): ship it.** Public repo, releases, install one-liner, demo GIF. Iterate from real use.

Stage 1 is mandatory and must be finished first.

## 1. What it does

```
$ ./gitlite init notes.txt          # start tracking notes.txt
$ ./gitlite commit "first draft"    # snapshot current notes.txt
$ ./gitlite log                     # list commits, newest first
$ ./gitlite diff 1 3                # what changed between commit 1 and 3
$ ./gitlite checkout 2              # restore notes.txt to commit 2 (pushes current id on undo stack)
$ ./gitlite undo                    # go back to where you were before the last checkout
$ ./gitlite status                  # current commit id, dirty/clean, undo depth
```

State lives in `.gitlite/` next to the file (M8). Until M8, everything is in memory and the program is a menu loop.

Stage 2 adds `push`, `pull`, `branch` and makes every item above operate on a real git repo.

## 2. Data structures — all hand-built, all templates, all header-only

| Structure | File | Used for | Must have |
|---|---|---|---|
| `List<T>` | `List.h` | the commit history | Node on heap, head/tail/size, push_back, push_front, pop_front, iteration (begin/end), destructor, copy ctor, copy assign, move ctor, move assign |
| `Stack<T>` | `Stack.h` | undo of checkouts | built ON `List<T>` (composition), push/pop/top/empty, throws `EmptyStackError` on pop/top when empty |
| `Commit` | `Commit.h` | one snapshot | `int id; std::string message; std::string content; std::time_t when;` plain struct |
| `Repository` | `Repository.h/.cpp` | the brain | `List<Commit> history; Stack<int> undo; int current;` + the commands |
| `Diff` | `Diff.h/.cpp` | M6 | `splitLines`, `lcs`, `printDiff` |
| exceptions | `Errors.h` | everywhere | `GitLiteError : std::runtime_error`; `EmptyStackError`, `NoSuchCommit`, `CorruptRepo` derive from it; Stage 2 adds `GitError` |
| `Backend` | `Backend.h` | M10+ | abstract class the menu talks to: `commit/log/checkout/undo/diff/status` pure virtual. `LocalBackend` wraps `Repository` (Stage 1); `GitBackend` wraps real git (Stage 2) |
| `Process` | `Process.h/.cpp` | Stage 2 | `Result run(const std::vector<std::string>& argv)` via fork/execvp/pipe/dup2/waitpid; `FileDesc` RAII wrapper for every fd |

No `std::list`, `std::stack`, `std::forward_list`. `std::vector` and `std::string` are allowed. Stage 2: no `std::system`, no `popen`.

## 3. File layout

```
gitlite/
  List.h          Stack.h         Errors.h        Commit.h
  Repository.h    Repository.cpp
  Diff.h          Diff.cpp
  Backend.h       LocalBackend.h  LocalBackend.cpp        (M10)
  Process.h       Process.cpp     GitBackend.h  GitBackend.cpp   (Stage 2)
  main.cpp        build.sh        Makefile
  tests/          README.md       SPEC.md
```

## 4. Stage 1 milestones — each ends: builds under ASan+UBSan, test passes, commit

**M1 — `List<T>` basics.** Node struct inside the class. `push_back`, `size`, `empty`, destructor that walks and deletes. Iterator with `operator*`, `operator++`, `operator!=`, and `begin()/end()` so range-for works.
*Prove:* push 1000 ints, range-for sums them, ASan silent. Comment out the destructor body → ASan reports the leak → put it back.

**M2 — Rule of three on `List<T>`.** Copy ctor (deep: walk `other`, push_back each), copy assignment (self-check, clear, copy), `clear()`.
*Prove:* `List<std::string> b = a;` modify `b`, `a` unchanged; `b = b;` harmless; both destruct clean.

**M3 — `Stack<T>` + first exception type.** `Errors.h` with the hierarchy. `Stack<T>` holds a `List<T>` (add `push_front`/`pop_front`, O(1)). `pop()` on empty throws `EmptyStackError`.
*Prove:* push 3, pop 4 → 4th throws; `catch (const GitLiteError& e)` prints `e.what()` and the program continues.

**M4 — `Commit` + `Repository::commit/log`.** `commit(msg)` reads the tracked file, pushes a `Commit` with next id and `std::time(nullptr)`. `log()` prints id, time, message, line count. Menu loop in `main.cpp`.
*Prove:* three commits, log shows three, newest first.

**M5 — checkout + undo.** `checkout(id)`: find the commit (throw `NoSuchCommit` if absent), push `current` onto `undo`, write content back, set `current = id`. `undo()`: pop → checkout that id without pushing.
*Prove:* commit A, B, C → checkout 1 → file has A → undo → back to C. `undo` on empty → clean error, no crash.

**M6 — diff via LCS.** Split into lines. LCS: (a) recursive, (b) memoized, (c) bottom-up tabulation. Walk the table back to emit ` ` / `-` / `+` lines.
*Prove:* diff of a commit with itself → no `+`/`-`; add one line → exactly one `+`. Time (a) vs (c) on 200 lines with chrono.

**M7 — Move semantics.** Move ctor + move assignment on `List<T>` (steal head/tail/size, null out `other`), `noexcept`. 1 MB commit: time `std::move` vs copy.
*Prove:* move ~0 ms, copy isn't; after move `a.size() == 0` and `a` destructs clean.

**M8 — Persistence.** `.gitlite/`: `<id>.txt` + `<id>.meta` per commit, `HEAD`, `UNDO`. Load on startup; missing dir = fresh repo. Malformed file → `CorruptRepo`, caught in `main`, program exits cleanly. Parse into temporaries first, then swap in.
*Prove:* commit, quit, restart, log matches; hand-corrupt a `.meta` → clean error.

**M9 — Smart-pointer refactor.** `std::unique_ptr<Node> next`, `unique_ptr<Node> head`, `tail` stays raw non-owning. Delete the destructor body. Copy ctor still hand-written. Move ops `= default`.
*Prove:* ASan silent with no hand-written delete. Push 1,000,000 ints → recursive destruction may overflow the stack → fix by popping iteratively. Document in README.

**M10 — `Backend` interface + ship Stage 1.** Abstract `Backend`; `LocalBackend : Backend` owns a `Repository`. Menu holds `std::unique_ptr<Backend>` and calls only through it. README, `tests/`, Makefile, push.
*Prove:* menu behaves exactly as before; `grep Repository main.cpp` finds nothing.

## 5. Stage 2 milestones — real git behind the same menu

Pre-req: `git push` already works from your terminal.

**M11 — `Process::run`.** `FileDesc` RAII (move-only). `run(argv)`: two `pipe()`s, `fork()`, child: `dup2`, `execvp`, `_exit(127)` on failure; parent: close write ends, read both pipes to EOF, `waitpid`, `WEXITSTATUS`. Syscall failure → `GitError(what + strerror(errno))`.
*Prove:* `run({"echo","hi"})` → `"hi\n"`, exit 0. `run({"ls","/nope"})` → exit ≠ 0, err non-empty. Missing binary → 127. No leaked fds after 100 runs. Commit message containing `"; rm -rf ~"` is just text.

**M12 — `GitBackend`.** `status` → `git status --porcelain=v1 -b`; `commit` → `git add -A` + `git commit -m`; `log` → `git log --oneline -n 20`; `checkout` → `git rev-parse --verify` then `git checkout`; `undo` → `git reset --soft HEAD~1`; `diff` → `git diff`; `push` → `git push` (retry `-u origin <branch>` on no upstream); `pull` → `git pull --rebase`; `branch` → list/create/switch. Non-zero exit → `GitError` with git's stderr.
*Prove:* commit + push from menu → visible on GitHub → pull on a second clone. Conflict → error shown, program alive. No `/bin/sh` spawned.

**M13 — Ship Stage 2.** Backend chosen from argv (`--local` = Stage 1; default = git if `.git/` exists). README entries 6–7. Alias on PATH; use it on `cpp-bootcamp`.

## 6. "What I learned" README entries (one paragraph each)
1. Nodes on the heap: who owns `next`; what ASan said when the destructor was missing.
2. Rule of three → five: what changed M2 → M7, why move is O(1).
3. Own exception type: why derive from `std::runtime_error`; catch at boundary, throw deep.
4. LCS: recursive → memoized → tabulated, with timings. Why this is DP.
5. `unique_ptr` nodes: what got simpler, the recursive-destruction overflow, the fix.
6. (Stage 2) fork/exec/pipes: child vs parent, `dup2` before `exec`, `_exit` not `exit`, the fd leak `FileDesc` prevents.
7. (Stage 2) Abstract `Backend`: what it cost in M10, what it saved in M12.

## 7. Done criteria
Stage 1: builds clean under `-Wall -Wextra -Werror -fsanitize=address,undefined`; every command works from the menu; every error path prints and continues; `tests/` has happy path, undo-on-empty, checkout-bad-id, corrupt-repo, diff-insert, diff-delete; README entries 1–5 + timings; pushed.

Stage 2: no `system()`/`popen()`; `GitError` on every failing git call; no leaked fds; commit + push + pull round-trip to GitHub from the menu; `tests/` adds run-echo, run-missing-binary, injection-message, push-no-upstream; README entries 6–7.

## 8. Stage 3 — ship (after M13)
- **S1** Own public repo, MIT LICENSE, README with pitch + GIF + install + usage, CONTRIBUTING.md, GitHub Actions (ASan+UBSan on macOS + Ubuntu), badge.
- **S2** Semver tags, GitHub Release with macOS + Linux binaries, install one-liner, `--version`.
- **S3** LinkedIn post (GIF + three sentences), one Show HN / r/cpp post.
- **S4** `ROADMAP.md`; issue → branch → PR habit; pick one wedge feature; measure with stars/clones/issues.

## 9. Stretch
- `branch`/`merge` in the Stage 1 engine (list becomes a tree)
- content hashing (FNV-1a) → Git-Lite v2 with own hash map
- edit distance instead of LCS for word-level diff
- Stage 2: conflict helper, `stash`, `git status` on every menu redraw
