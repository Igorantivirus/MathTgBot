<h1 align="center">Math Gadalka Telegram Bot</h1>

[![Русская версия](https://img.shields.io/badge/Русская%20версия-blue)](README_RU.md)

<h3>Live Bot</h3>

- Link: https://t.me/GadalkaMathBot
- Username: @GadalkaMathBot

<h2>Overview</h2>

A Telegram bot written in C++ that evaluates mathematical expressions, including inline mode.
It supports both basic and advanced functions in the following categories:

- Arithmetic operations
- Trigonometric functions
- Logarithms
- Powers

Computation is powered by a custom engine/library.

<h2>Tech Stack</h2>

Language standard: **C++23**

Dependencies:
- [tgbot-cpp](https://github.com/reo7sp/tgbot-cpp) — Telegram Bot API for C++
- [nlohmann-json](https://github.com/nlohmann/json) — JSON processing
- [sqlite3](https://sqlite.org/download.html) — embedded SQL database
- [MathWorker](https://github.com/Igorantivirus/MathWorker) — C++ library for mathematical expressions

<h2>Roadmap</h2>

- Bot settings: buttons and menu
- More predefined functions and examples
- Multi-line/systems of expressions mode

<h2>Build</h2>

1. <b>Clone the repository</b>

   ```sh
   git clone https://github.com/Igorantivirus/MathTgBot
   cd MathTgBot
   ```
2. <b>Generate CMake files</b>

   ```sh
   cmake -B build
   ```
3. <b>Build</b>

   ```sh
   cmake --build build --config Release
   ```
4. <b>Configure</b>

   Edit `assets/mainConfig.json`. At minimum:
   - Provide the bot API token
   - Ensure the path to `assets/responseConfig.json` is correct
5. <b>Run</b>

   From the `build` directory, run the executable `MathBot`,
   passing the path to `assets/mainConfig.json`:

   ```sh
   ./MathBot "path/assets/mainConfig.json"
   ```

<h2>License</h2>

**MIT License**
﻿
