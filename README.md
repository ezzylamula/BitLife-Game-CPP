# BitLife-inspired C++ Game

This project is a lightweight desktop life simulator inspired by BitLife. It is built in C++ and runs as a terminal-based game with a simple menu-driven interface.

## Features

- Character creation with a custom name
- Age progression through game months
- Education and intelligence growth
- Jobs and income management
- Relationships and happiness tracking
- Random life events
- Health, energy, and stress systems
- End-of-life summary

## Requirements

- CMake 3.16+
- A C++17-compatible compiler

## Build

```bash
cmake -S . -B build
cmake --build build
```

## Run

```bash
./build/bitlife
```

## Notes

This is a playable prototype designed to capture the feel of a life-sim game. It is intentionally simple and terminal-based so it works on desktop platforms without extra dependencies.

If you want, this can be expanded later with:

- a real graphical interface
- more life events and decisions
- family and children systems
- city and career progression
- save/load support
