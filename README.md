# Intro
These are mini projects that I created as a part of learning CPP on my journey to explore Computer Science. Here are short descriptions of the projects that are in this repo. 



## MineSweeper (C++ Console)

A simple text-based Minesweeper game for macOS, written in C++ and designed for CLion.
Fixed board: **8 rows × 5 columns**, **10 mines**.

### How to Play

Commands are 3 characters:

* `fIJ` — Flag cell at row `I`, col `J`
* `uIJ` — Unflag cell at row `I`, col `J`
* `rIJ` — Reveal cell at row `I`, col `J`

Example: `f12` (flag row 1, col 2).
Game ends when all mines are flagged (win) or a mine is revealed (loss).

### Build & Run

**With g++**

```
g++ -std=c++17 -O2 -o minesweeper main.cpp
./minesweeper
```

**With CLion**
Open the project, replace `main.cpp` with the provided source, and run.


### Display Symbols

* `-` : Unknown cell
* `!` : Flagged mine
* `*` : Mine (shown after losing)
* `&` : Incorrect flag (shown after losing)
* `0..8` : Adjacent mine count

### What I Learned

* Using constants for game states instead of “magic numbers”
* Writing modular code with helper functions
* Implementing basic game logic with conditionals
* Working with random number generation in C++
* Managing game state without arrays (using individual variables)
