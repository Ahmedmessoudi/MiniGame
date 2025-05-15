[![C++ Version](https://img.shields.io/badge/C%2B%2B-17-blue?logo=c%2B%2B&style=flat-square)](https://isocpp.org/)  
[![SFML](https://img.shields.io/badge/SFML-2.5-orange?logo=sfml&logoColor=white&style=flat-square)](https://www.sfml-dev.org/)  
[![Build Status](https://img.shields.io/github/actions/workflow/status/Ahmedmessoudi/MiniGame/ci.yml?branch=main&style=flat-square)](https://github.com/Ahmedmessoudi/MiniGame/actions)  
[![License](https://img.shields.io/github/license/Ahmedmessoudi/MiniGame?style=flat-square)](LICENSE)

# MiniGame: Classic Pong in C++

A simple, classic Pong clone written in C++. Demonstrates  
paddle & ball movement, real-time input handling, collision detection,  
and scoring—all built with the [SFML library](https://www.sfml-dev.org/) :contentReference[oaicite:0]{index=0}.

---

## Table of Contents

- [Features](#features)  
- [Prerequisites](#prerequisites)  
- [Building](#building)  
- [Running](#running)  
- [Controls](#controls)  
- [Project Structure](#project-structure)  
- [Contributing](#contributing)  
- [License](#license)  

---

## Features

- **Two-player** Pong on a single keyboard  
- **Smooth** ball & paddle movement  
- **Collision** detection with window bounds & paddles  
- **Score tracking** and reset on goal  

---

## Prerequisites

- **C++17** compliant compiler (e.g., `g++`, `clang++`) :contentReference[oaicite:1]{index=1}  
- **CMake** ≥ 3.10 (or any build system you prefer)  
- **SFML** ≥ 2.5 for graphics, windowing, and input :contentReference[oaicite:2]{index=2}  

---

## Building

```bash
# Clone the repo
git clone https://github.com/Ahmedmessoudi/MiniGame.git
cd MiniGame

# Create a build directory
mkdir build && cd build

# Configure & build
cmake ..
make


# Executable 'Pong' will be in build/

g++ -std=c++17 -I/path/to/SFML/include ../src/*.cpp \
    -o Pong \
    -L/path/to/SFML/lib -lsfml-graphics -lsfml-window -lsfml-system
```
## 🎮 Controls

| **Paddle**        | **Up** | **Down** |
| :---------------- | :----: | :------: |
| 🟦 **Left Paddle**  | `W`    | `S`      |
| 🟥 **Right Paddle** | `↑`    | `↓`      |
| ⏹️ **Quit Game**    | —      | `Esc`    |

---

## 📂 Project Structure

```text
📁 MiniGame/
├── ⚙️  CMakeLists.txt           # Build configuration
├── 📂  src/                     # Source code
│   ├── 📄  main.cpp
│   ├── 📄  Paddle.cpp
│   ├── 📄  Ball.cpp
│   └── … 
├── 📂  include/                 # Header files
│   ├── 📄  Paddle.h
│   ├── 📄  Ball.h
│   └── … 
├── 🎨  assets/                  # (Optional) textures, fonts, etc.
└── 📄  README.md                # ← You are here

