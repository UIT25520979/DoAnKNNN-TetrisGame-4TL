# 🕹️ SURVIVAL TETRIS GAME

<p align="center">
  <img src="https://img.shields.io/badge/C++-17-blue.svg?logo=c%2B%2B" />
  <img src="https://img.shields.io/badge/Raylib-5.5.0-red.svg?logo=raylib" />
  <img src="https://img.shields.io/badge/License-MIT-green.svg" />
  <img src="https://img.shields.io/badge/Build-MinGW--w64-orange.svg" />
</p>

## 📌 Project Overview

| Category               | Details                    |
| ---------------------- | -------------------------- |
| **Core Language**      | C++17                      |
| **Graphics Library**   | Raylib 5.5.0               |
| **Toolchains**         | MinGW-w64 / Visual Studio  |
| **Target OS**          | Windows x64                |
| **Course**             | Professional Skills (SS004)|
| **Host Institution**   | UIT - VNU-HCM              |
| **Faculty Supervisor** | Nguyen Van Toan            |

**Survival Tetris Game** is a modern 2D survival puzzle game developed using **C++17** and **Raylib 5.5.0**. The project modernizes traditional Tetris gameplay by integrating modular software architecture, dynamic visual effects, adaptive difficulty systems, particle simulations, custom audio management, and persistent high-score storage.

---

## 📚 Table of Contents

* [📌 Project Overview](#-project-overview)
* [✨ Key Features](#-key-features)
* [📁 Directory Structure](#-directory-structure)
* [🎮 Core Gameplay Components](#-core-gameplay-components)
* [⌨️ Control Mapping](#️-control-mapping)
* [⚙️ Build & Compilation](#️-build--compilation)
* [🚀 Official Release](#-official-release)

---

## ✨ Key Features

### 🧩 Modular Architecture

Separation between **game logic**, **rendering systems**, and **data structures** to reduce coupling and improve maintainability.

### 🎲 7-Bag Tetromino System

Implements a fair-play randomization system that evenly distributes all **7 Tetromino pieces**, preventing repetitive block streaks.

### 📈 Adaptive Difficulty Scaling

Three difficulty levels:

* **Easy**
* **Medium**
* **Hard**

Each mode dynamically adjusts:

* Falling speed
* Score multipliers
* Gameplay intensity

### 🎵 Context-Aware Audio System

Supports:

* Background music (BGM)
* Sound effects (SFX)
* Smooth scene transitions
* Concurrent audio channels

### ✨ Particle Simulation Effects

Includes custom **2D particle physics** for:

* Row-clearing animations
* Impact feedback
* Visual polish

### 📳 Camera Screen Shake

Dynamic viewport displacement during:

* Tetris clears
* Heavy impacts
* Game Over sequences

### 💾 Persistent High Scores

Top 5 scores are serialized locally into:

```txt
highscore.txt
```

### 🖼️ Native Resource Embedding

Custom:

* Window icon
* Taskbar icon
* Runtime metadata

embedded directly into the executable.

### ⚡ Zero-Dependency Build

Supports standalone compilation with embedded framework linking.

### 🧠 Leak-Free Memory Layout

Carefully managed memory cleanup to avoid long-session RAM bloat.

---

## 📁 Directory Structure

```text
TetrisGame/
├── .vscode/
│   ├── c_cpp_properties.json
│   ├── launch.json
│   └── tasks.json
│
├── assets/
│   ├── audio/
│   ├── data/
│   └── images/
│
├── include/
│   ├── audiohandler.h
│   ├── common.h
│   ├── effects.h
│   ├── gamedata.h
│   ├── gamelogic.h
│   ├── menu.h
│   ├── menudata.h
│   ├── monument.h
│   └── piece.h
│   └── raylib.h
│   └── raymath.h
│
├── src/
│   ├── audiohandler.cpp
│   ├── effects.cpp
│   ├── gamedraw.cpp
│   ├── gamelogic.cpp
│   ├── main.cpp
│   ├── menudraw.cpp
│   ├── menulogic.cpp
│   ├── monument.cpp
│   └── piece.cpp
│
├── lib/
│   ├── libraylib.a
│   ├── raylib.lib
│   
├── icon.rc
└── TetrisGameCode-4TL.vcxproj
└── TetrisGameCode-4TL.vcxproj.filters
└── packages.config
```

---

## 🎮 Core Gameplay Components

The game is managed using a **Finite State Machine (FSM)**.

| Game State           | Description                                                    |
| -------------------- | -------------------------------------------------------------- |
| `STATE_MENU`         | Main menu interface handling UI interactions and scene routing |
| `STATE_LEVEL_SELECT` | Difficulty selection and score multiplier configuration        |
| `STATE_THEME_SELECT` | Theme switching (Space, Jungle, Egypt)                         |
| `STATE_PLAYING`      | Core gameplay loop including movement, collision, and scoring  |
| `STATE_MONUMENT`     | Displays Top 5 persistent high scores                          |
| `STATE_GAMEOVER`     | Handles score validation and end-game logic                    |

---

## ⌨️ Control Mapping

| Key     | Action                     |
| ------- | -------------------------- |
| `A`     | Move Tetromino left        |
| `D`     | Move Tetromino right       |
| `W`     | Rotate Tetromino clockwise |
| `S`     | Soft Drop                  |
| `Space` | Hard Drop                  |

---

## ⚙️ Build & Compilation

### 1. Compile Native Resources

```bash
windres icon.rc -O coff -o icon.o
```

### 2. Build Project in VS Code

Open the repository in **Visual Studio Code** and press:

```txt
Ctrl + Shift + B
```

The automated build system configured in:

```txt
.vscode/tasks.json
```

will compile the project and link required dependencies:

```txt
-lraylib
-lopengl32
-lgdi32
-lwinmm
```

Output executable:

```txt
SurvivalTetrisGame.exe
```

---

## 🚀 Official Release

The production build of **Survival Tetris Game** are now available via **GitHub Releases**.

The release package will include:

```text
SurvivalTetrisGame.exe
assets/
```

allowing players to run the game immediately on any Windows machine without additional installation.

We welcome everyone to clone the repository, test their survival strategies, explore custom themes, and compete for the highest score on the **Eternal Monument** leaderboard.

---

## ⭐ Support the Project

If you enjoy this project, consider giving the repository a **star ⭐** on GitHub.
