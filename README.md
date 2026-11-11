# Euchre Card Game (C++)

[![CI](https://github.com/VishChalla/EuchreCardGame/actions/workflows/ci.yml/badge.svg)](https://github.com/VishChalla/EuchreCardGame/actions/workflows/ci.yml)
![C++17](https://img.shields.io/badge/C%2B%2B-17-blue)

A command-line simulation of one hand of Euchre between four computer players, written in C++17. It shuffles and deals a 24-card pack, turns up a card to propose trump, lets players order it up based on hand strength, then plays out five tricks and prints every step.

```
Top card turned up:
----------------
9 of Hearts
----------------

playerOne has declared Hearts as trump!

TRICK 1
///////////////////////////////////////
playerOne plays: Jack of Hearts
playerTwo plays: Ace of Hearts
playerThree plays: Jack of Diamonds
playerFour plays: King of Hearts
-------------------------------
playerOne has won the trick!
-------------------------------
```

## How it works

| File | Responsibility |
|---|---|
| [`src/Deck.cpp`](src/Deck.cpp) | Builds the 24-card pack and shuffles it, with an optional seed for repeatable games |
| [`src/Dealer.cpp`](src/Dealer.cpp) | Deals in the traditional 2-3 or 3-2 pattern, settles trump, scores cards, decides each trick |
| [`src/Player.cpp`](src/Player.cpp) | Chooses which card to play |
| [`src/main.cpp`](src/main.cpp) | Runs and narrates one hand |
| [`tests/Test.cpp`](tests/Test.cpp) | Unit tests plus 1,000 seeded full games |

**Card strength.** Each card gets a score for the current trump suit, from the right bower (jack of trump, 1.00) and left bower (jack of the same colour, 0.76) down to off-suit low cards (0.01). The values approximate each card's chance of winning a trick.

**Strategy.** A player orders up trump when holding something stronger than the trump ace, and on each trick leads their strongest trump, or their strongest card if they have none.

## Build and run

With CMake:

```bash
cmake -S . -B build
```

```bash
cmake --build build
```

```bash
ctest --test-dir build --output-on-failure
```

```bash
./build/euchre 42
```

Or directly with a compiler:

```bash
g++ -std=c++17 -Isrc src/Deck.cpp src/Player.cpp src/Dealer.cpp src/main.cpp -o euchre
```

Run `./euchre` for a random game, or pass a number such as `./euchre 42` to replay the same shuffle.

## What I fixed in the 2026 cleanup

The first version of this project crashed on some shuffles and I could not find why at the time. Coming back to it, the causes were:

- the card-choosing loop erased from one list while indexing another, so the two fell out of step and the "card played" index could point outside the hand
- the trick winner was computed over an array one element longer than the number of players, reading uninitialised memory
- `std::random_shuffle`, which was removed in C++17

The rewrite replaces these with bounds-safe code, adds seeded shuffles so any game can be reproduced, and adds a test that plays 1,000 full games to completion.

## Simplifications

This is a simulation of the game's core mechanics, not a full rules engine. Not implemented: following suit, a second bidding round when nobody orders up, the dealer picking up the turned card, going alone, partnerships and scoring across hands.
