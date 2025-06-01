# Word Ladder Game

A modern C++ implementation of the classic Word Ladder puzzle game with a Qt-based graphical user interface. This game challenges players to transform one word into another by changing one letter at a time, with each intermediate word being valid.

## Features

### Multiple Game Modes

1. **Auto Mode**
   - Automatically finds the shortest path between any two words
   - Supports different word lengths (3-10 letters)
   - Instant path visualization

2. **Play Mode**
   - Interactive gameplay with start and target words
   - Real-time word validation
   - Hint system to help players
   - Progress tracking and move counting
   - Player statistics and game history

3. **Analytics Mode**
   - Track player performance
   - View game history
   - Analyze optimal vs. actual moves
   - Monitor hint usage

### Technical Features

- Efficient graph-based word path finding
- Dictionary management with support for different word lengths
- Modern Qt-based GUI with intuitive interface
- Game state persistence and statistics tracking
- Comprehensive error handling and user feedback

## Requirements

- C++17 or later
- Qt 6.x
- CMake 3.16 or later
- A C++ compiler with C++17 support (e.g., GCC, MSVC, Clang)

## Building the Project

1. Clone the repository:
   ```bash
   git clone https://github.com/stazoone/WordLadder
   cd word-ladder-game
   ```

2. Create a build directory:
   ```bash
   mkdir build
   cd build
   ```

3. Configure and build:
   ```bash
   cmake ..
   cmake --build .
   ```

## Running the Application

After building the project, you can run the application:

1. On Windows:
   ```bash
   .\Debug\WordLadder.exe
   ```

2. On Linux/macOS:
   ```bash
   ./WordLadder
   ```

Make sure you have the dictionary files in the same directory as the executable before running the application.

## Dictionary Files

The game requires dictionary files named `dict_[length].txt` in the application directory, where `[length]` is the word length (e.g., `dict_4.txt` for 4-letter words). Each dictionary file should contain one word per line.

## How to Play

1. **Auto Mode**
   - Select word length
   - Load dictionary
   - Enter start and target words
   - Click "Find Path" to see the shortest solution

2. **Play Mode**
   - Enter your player name
   - Select word length
   - Click "Start Game"
   - Transform the start word into the target word by changing one letter at a time
   - Use hints if needed
   - Submit each word to progress

3. **Analytics**
   - Enter player name to view statistics
   - See game history and performance metrics
