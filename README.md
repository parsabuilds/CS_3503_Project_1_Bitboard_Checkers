# CS 3503 Project 1: BitBoard Checkers

This project is a complete checkers game implemented in C, developed for the Owl Tech Industries Software Engineering Internship Program. The core requirement is the use of **bitboards**—representing the game state with 64-bit integers—to learn and apply efficient bit manipulation techniques common in high-performance game engines.

---
## Core Features
* **Bitboard Representation**: The entire game state, including piece locations and types, is managed using `unsigned long long` integers.
* **Complete Game Logic**: Implements standard checkers rules for piece movement, captures, and king promotion.
* **Win Detection**: The game correctly identifies when a player has no pieces remaining and declares a winner.
* **Interactive ASCII Interface**: A clear, text-based interface for displaying the board and accepting user input.

---
## How to Build and Run

### Prerequisites
You need a C compiler (like **GCC**) and the **make** utility. These are standard in most Linux and WSL environments.

### Compilation
Navigate to the project directory in your terminal and run the `make` command:
```bash
make
```

## How to Play the Game 
### The Objective 
The goal is to capture all of your opponent's pieces. The game ends when one player has no pieces left on the board.

### The Board
The game is played on an 8x8 grid where squares are numbered from 0 to 63. Pieces only move on the dark squares, which are represented by a . when empty.

- r / b: Red and Black "men" (regular pieces).

- R / B: Red and Black "Kings".

- .: An empty, playable dark square.

- #: An unusable light square.

### Making a Move
The game will prompt the current player for a move. Red (r) always starts.

The input format must be two numbers separated by a single space: from_square to_square, followed by pressing Enter.
1. Simple Move: To move a piece forward diagonally to an adjacent empty square.
    - Example: To move a piece from square 16 to 25, you would type:
    '''bash
    Enter move: 16 25
    '''
2. Capture Move (Jump): To jump over an opponent's piece to an empty square on the other side. Captures are mandatory if available in standard checkers, but optional for this project's implementation.
    - Example: A red piece is on 9 and a black piece is on 18. To jump and capture the black piece, you would move to square 27. Type:
    '''bash
    Enter move: 9 27
    '''
The black piece at square 18 will be removed from the board.

### King Promotion
When a regular piece (a "man") reaches the opponent's back row, it is promoted to a King. Kings are shown as an uppercase letter (R or B) and have the powerful ability to move and capture both forwards and backwards.