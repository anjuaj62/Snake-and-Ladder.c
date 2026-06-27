# 🎲 Snake and Ladder Game — C Programming

A fully functional **Snake and Ladder** game that runs in the terminal, written in pure C using structured functions.  
Built as a C programming project to demonstrate functions, arrays, loops, and game logic.

---

## 📸 Preview

```
===== Snake and Ladder Game =====

Enter number of players (2 to 10): 2

  Snakes  (slide DOWN): 17->7  | 54->34 | 62->19
  Ladders (climb UP)  :  3->22 | 25->45 | 56->78
  Roll a 1 to enter. Roll a 6 for an extra turn.

---------------------------------
Player 1's turn  (not on board yet)
Press ENTER to roll...
Dice = 1
  Player 1 entered the board at square 1!

---------------------------------
Player 2's turn  (not on board yet)
Press ENTER to roll...
Dice = 4
  Need a 1 to enter. Better luck next turn!

---------------------------------
Player 1's turn  (at square 1)
Press ENTER to roll...
Dice = 2
  Player 1 moved to square 3.
  *** LADDER! Climb from 3 up to 22! ***
```

---

## ✨ Features

- **2 to 10 players** supported
- **Must roll a 1** to enter the board
- **Rolling a 6** grants a bonus extra turn
- **3 Snakes** that slide you down
- **3 Ladders** that climb you up
- Must land **exactly on 100** to win
- Clean function-based code structure

---

## 🗺️ Board Layout

```
 100  99  98  97  96  95  94  93  92  91
  81  82  83  84  85  86  87  88  89  90
  80  79  78  77  76  75  74  73  72  71
  61  62  63  64  65  66  67  68  69  70
  60  59  58  57  56  55  54  53  52  51
  41  42  43  44  45  46  47  48  49  50
  40  39  38  37  36  35  34  33  32  31
  21  22  23  24  25  26  27  28  29  30
  20  19  18  17  16  15  14  13  12  11
   1   2   3   4   5   6   7   8   9  10
```

### 🐍 Snakes

| Head (start) | Tail (end) | Effect        |
|:------------:|:----------:|:-------------:|
| 17           | 7          | Slide down 10 |
| 54           | 34         | Slide down 20 |
| 62           | 19         | Slide down 43 |

### 🪜 Ladders

| Foot (start) | Top (end) | Effect      |
|:------------:|:---------:|:-----------:|
| 3            | 22        | Climb up 19 |
| 25           | 45        | Climb up 20 |
| 56           | 78        | Climb up 22 |

---
## 🎮 How to Play

| Step | Action |
|------|--------|
| 1 | Run the program and enter number of players (2–10) |
| 2 | Each player presses **ENTER** to roll the dice |
| 3 | You must roll a **1** to enter the board |
| 4 | Move forward by the dice number each turn |
| 5 | Land on a 🪜 Ladder foot → climb up automatically |
| 6 | Land on a 🐍 Snake head → slide down automatically |
| 7 | Roll a **6** → get an extra turn immediately |
| 8 | First player to land **exactly on 100** wins! |

> ⚠️ If your roll would take you past 100, you stay in place and wait for the right number.

---

## 🧩 Code Structure

The game is built using **7 functions**, each with a single clear responsibility:

```
main()
 ├── setup_game()       — get player count, initialise arrays
 └── play_game()        — main game loop
      └── take_turn()   — one player's full turn
           ├── roll_dice()       — returns random 1–6
           ├── move_player()     — move + check win
           │    ├── check_ladder()  — climb up if on ladder foot
           │    └── check_snake()   — slide down if on snake head
```

### Function Summary

| Function | Purpose | Returns |
|----------|---------|---------|
| `setup_game()` | Ask player count, initialise position and started arrays | void |
| `roll_dice()` | Generate random number 1 to 6 | int (1–6) |
| `check_ladder(pos)` | If pos is ladder foot, return top. Else return pos | int |
| `check_snake(pos)` | If pos is snake head, return tail. Else return pos | int |
| `move_player(player, dice)` | Move player, apply ladder/snake, check win | int (1=win) |
| `take_turn(player)` | Full turn: enter rule, move, extra turn on 6 | int (1=win) |
| `play_game()` | Loop all players until someone wins | void |

---

## 🧠 Concepts Used

- Functions with parameters and return values
- Global arrays (`position[]`, `started[]`)
- `for` and `while` loops
- `rand()` and `srand()` for random dice
- `scanf()` and `getchar()` for input
- `#define` constants for board size
- Parallel arrays for snake and ladder mappings
