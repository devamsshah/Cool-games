# C++ Mini Projects

These are mini projects that I created as part of learning C++ on my journey to explore Computer Science.
Each project taught me different aspects of programming, problem-solving, and structuring code.
Below are short descriptions of the projects in this repo.

---

## 1. MineSweeper (C++ Console)

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

```bash
g++ -std=c++17 -O2 -o minesweeper minesweeper.cpp
./minesweeper
```

**With CLion** — Open project, replace `main.cpp` with source, run.

### Display Symbols

* `-` : Unknown cell
* `!` : Flagged mine
* `*` : Mine (after losing)
* `&` : Incorrect flag (after losing)
* `0..8` : Adjacent mine count

### What I Learned

* Using constants for game states instead of magic numbers
* Writing modular code with helper functions
* Implementing random mine placement
* Managing game state without arrays (learning exercise)

---

## 2. Yahtzee (C++ Console)

A playable console version of the classic **Yahtzee** dice game.
Implements all scoring categories and game flow with rolling, keeping, and scoring dice.

### How to Play

* You start with 5 dice.
* Roll them, choose which dice to keep (`Keep Dice (s to stop rolling)`), and roll the rest up to **3 times per turn**.
* Select a scoring category to play your dice in.
* Game ends when all 13 categories have been played.
* The board updates automatically with your scores and bonus (if applicable).

### Build & Run

**With g++**

```bash
g++ -std=c++17 -O2 -o yahtzee yahtzee.cpp
./yahtzee
```

**With CLion** — Open project, replace `main.cpp` with source, run.

### Features

* Full Yahtzee scorecard (Upper + Lower sections)
* Automatic bonus calculation when Upper Section ≥ 63
* All rules implemented: Three/Four of a Kind, Full House, Straights, Chance, Yahtzee
* Sorting and frequency counting to detect scoring patterns
* Prevents replaying a category already used

### What I Learned

* Using classes (`Dice`, `Hand`, `Game`) to structure a larger program
* Applying arrays and object arrays to manage game state
* Implementing scoring logic with conditionals and frequency counts
* Detecting poker-like patterns in sorted data
* Separating UI (`show()`) from logic (`calcScore()`)

---

## 3. IMDB Search Tool (C++ Console)

A command-line program to search and explore movie and actor/actress data from TSV (tab-separated) files modeled after IMDb datasets.

### How to Use

When running the program, you are presented with a menu:

1. **Search for movies** — Enter keywords (separated by `+`) to find matching movies, then select one to view its actors/actresses.
2. **Search for actors/actresses** — Enter keywords (separated by `+`) to find matching people, then select one to view their movies.
3. **Exit** — Quit the program.

Example:

```
Select a menu option:
    1. Search for movies
    2. Search for actors/actresses
    3. Exit
Your choice --> 1
Enter search phrase: godfather
0:
Title: The Godfather
Year: 1972
Genre: Crime Drama
---------------
Select a movie to see its actors/actresses (-1 to go back to the previous menu):
```

### Build & Run

**With g++**

```bash
g++ -std=c++17 -O2 -o imdb imdb.cpp
./imdb
```

Make sure the following files are in the same directory:

* `movie.titles.tsv`
* `movie.names.tsv`
* `movie.principals.tsv`

**With CLion** — Open project, ensure the TSV files are accessible from the working directory, and run.

### Features

* Reads IMDb-style TSV files into C++ structs and vectors
* Case-insensitive, multi-word search (`+` separated)
* Displays movie details (title, year, genre)
* Lists actors/actresses for a selected movie
* Lists movies for a selected actor/actress

### What I Learned

* Parsing tab-separated files into structured data (`struct`)
* Implementing search with partial and case-insensitive matching
* Linking related datasets via shared IDs
* Splitting program logic into reusable helper functions
* Handling vector-based data filtering and printing results

---

## 4. Node Graph Creator (C++ Console)

A tool to read an **edge list** from a file, store it as an adjacency list using linked lists, and write the adjacency list to a file.
Also prints graph statistics like number of nodes, edges, and maximum degree.

### How to Use

1. Prepare an edge list file (e.g., `karate.txt`) with pairs of integers per line:

```
0 1
0 2
1 2
...
```

2. Run the program — it will:

   * Load the graph from the edge list file
   * Create an adjacency list in memory
   * Save the adjacency list to `karate_adj.txt`
   * Print the adjacency list and graph statistics to the console

### Build & Run

**With g++**

```bash
g++ -std=c++17 -O2 -o nodegraph node_graph.cpp
./nodegraph
```

**With CLion** — Open project, set the working directory to where your edge list file is stored, and run.

### Features

* Stores graph as adjacency list using a `Node` linked list structure
* Adds edges in sorted order and prevents duplicates
* Reads from edge list file and outputs adjacency list file
* Prints:

  * Number of nodes
  * Number of edges
  * Maximum degree (max number of neighbors for any node)

### What I Learned

* Implementing adjacency lists with custom linked list nodes
* Managing dynamic memory structures without STL containers for neighbors
* File I/O for reading and writing graph data
* Computing graph metrics (degree, node count, edge count)
* Handling sorted insertion into a linked list

---

## 5. Password Checker (C++ Console)

A program that validates passwords against a series of security rules, including complexity requirements, leak checks, and dictionary word checks.

### How to Use

When you run the program, it will:

1. Prompt you to enter a password.

2. Validate it against these rules:

   * At least **8 characters** long
   * At least **1 uppercase** letter
   * At least **1 lowercase** letter
   * At least **1 digit**
   * At least **1 special character** (`@ ! # ^ & * $`)
   * Must **not** be present in the leaked passwords file
   * Must **not** contain a full English dictionary word

3. If the password fails any rule, an appropriate message is displayed, and the password is rejected.

Example:

```
Enter password: Passw0rd!
Password accepted!
```

### Build & Run

**With g++**

```bash
g++ -std=c++17 -O2 -o password_checker password_checker.cpp
./password_checker
```

Make sure the following files are in the same directory:

* `alleged-gmail-passwords.txt` (list of leaked passwords)
* `words_5.txt` (list of English words)

**With CLion** — Open project, ensure the required files are in the working directory, and run.

### Features

* Checks password complexity with multiple rules
* Binary search for leaked password detection
* Strips numbers/special characters to detect embedded dictionary words
* Loads leaked password list and dictionary list from files
* Displays detailed reasons for rejection

### What I Learned

* Using `isupper`, `islower`, `isdigit`, and ASCII value checks for validation
* Implementing binary search for fast lookups
* Parsing and cleaning input strings
* Validating multiple rules in sequence and providing feedback
* File I/O and vector storage for large datasets

---

## 6. Layered Pine Tree (C++ Console)

A program that displays either an ASCII "HELLO" graphic or an ASCII layered pine tree based on user menu selection.

### How to Use

When you run the program, you will see a menu:

```
Program 1: The Pine Tree
Choose from the following options:
   1. Display the HELLO graphic
   2. Display The Pine Tree
   3. Exit the program
Your choice ->
```

* **Option 1**: Displays a framed ASCII art spelling **HELLO**. You can choose the frame character.
* **Option 2**: Prompts for the number of tree layers, then displays an ASCII layered pine tree with a trunk (`|||`).
* **Option 3**: Exits the program.

Example for 3 layers:

```
Number of tree layers -> 3

    *
   ***
  *****
   ***
  *****
 *******
  *****
 *******
 *********
    |||
    |||
    |||
    |||
    |||
    |||
```

### Build & Run

**With g++**

```bash
g++ -std=c++17 -O2 -o pine_tree pine_tree.cpp
./pine_tree
```

**With CLion** — Open the project, run, and follow the menu prompts.

### Features

* Menu-based interface with three options
* Customizable frame character for "HELLO" graphic
* Layered tree drawing based on user-specified number of layers
* Dynamic trunk height proportional to the number of layers

### What I Learned

* Using `setw` and `setfill` from `<iomanip>` for alignment and padding
* Designing menu-based programs with `if`/`else if` branching
* Nested loops for generating ASCII art patterns
* Maintaining alignment with dynamic variables (`indent`, `originalIndent`)
* Combining decorative ASCII output with logic for user-controlled graphics
