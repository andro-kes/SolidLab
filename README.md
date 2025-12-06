# SolidLab - Dungeon Editor

A C++ dungeon editor implementing design patterns for managing and simulating NPC battles.

## Features

- **NPCs**: Orc, Bear, and Squirrel with unique names and coordinates (0-500)
- **Factory Pattern**: Creation and file I/O for NPCs
- **Visitor Pattern**: Battle cycle implementation
- **Observer Pattern**: Console and file logging
- **Smart Pointers**: Safe memory management with std::shared_ptr
- **STL Containers**: std::vector for efficient NPC management

## Battle Rules

- **Orc**: Kills Orcs and Bears within 100 units range
- **Bear**: Kills Squirrels within 100 units range  
- **Squirrel**: Does not attack
- Defeated NPCs are removed from the dungeon

## Building

```bash
mkdir build
cd build
cmake ..
make
```

To build with testing (enabled by default):
```bash
mkdir build
cd build
cmake -DBUILD_TESTING=ON ..
cmake --build .
```

To build without testing:
```bash
mkdir build
cd build
cmake -DBUILD_TESTING=OFF ..
cmake --build .
```

## Usage

Run the editor:
```bash
./build/dungeon_editor
```

### Menu Options

1. **Add NPC** - Create a new NPC with unique name and coordinates
2. **List NPCs** - Display all NPCs in the dungeon
3. **Save to file** - Save current dungeon state to a file
4. **Load from file** - Load dungeon state from a file
5. **Battle cycle** - Run one battle cycle (NPCs attack nearby enemies)
6. **Exit** - Quit the editor

### Example Session

```
1. Add NPC
   - Type: Orc
   - Name: Grom
   - Coordinates: (100, 100)

2. Add more NPCs...

3. Save to file: dungeon.txt

4. Battle cycle
   - Orc 'Grom' killed Bear 'Bruno' at (120, 110)
   - Bear 'Bruno' killed Squirrel 'Chip' at (130, 105)
```

## Design Patterns

### Factory Pattern
`NPCFactory` class handles:
- NPC creation by type
- Saving dungeon state to file
- Loading dungeon state from file

### Visitor Pattern
`BattleVisitor` class implements:
- Visit methods for each NPC type
- Battle logic and range checking
- Removal of defeated NPCs

### Observer Pattern
Two observers monitor battles:
- `ConsoleObserver`: Prints battle events to console
- `FileObserver`: Logs battle events to log.txt

## Architecture

```
include/
  ├── NPC.h           - Base NPC class
  ├── Orc.h           - Orc implementation
  ├── Bear.h          - Bear implementation
  ├── Squirrel.h      - Squirrel implementation
  ├── NPCFactory.h    - Factory pattern
  ├── BattleVisitor.h - Visitor pattern
  └── Observer.h      - Observer pattern

src/
  ├── main.cpp        - Main application
  ├── NPC.cpp         - Base NPC implementation
  ├── Orc.cpp         - Orc implementation
  ├── Bear.cpp        - Bear implementation
  ├── Squirrel.cpp    - Squirrel implementation
  ├── NPCFactory.cpp  - Factory implementation
  ├── BattleVisitor.cpp - Visitor implementation
  └── Observer.cpp    - Observer implementation
```

## Testing

The project uses GoogleTest for unit testing. Tests are built by default but can be disabled with `-DBUILD_TESTING=OFF`.

### Running Tests with CTest

After building with testing enabled:

```bash
cd build
ctest --output-on-failure
```

This runs all tests and shows output only for failed tests.

For verbose output:
```bash
ctest -V
```

### Running Tests Directly

You can also run the test binary directly for more detailed output:

```bash
cd build
./dungeon_tests
```

### Test Coverage

The test suite includes:

- **Battle Logic Tests**: Verify NPC attack rules, range checking, and combat scenarios
  - Orc kills Orcs and Bears within 100 units
  - Bear kills Squirrels within 100 units
  - Squirrel doesn't attack
  - No attacks outside range
  - Self-attack prevention
  
- **Factory Tests**: Verify NPC creation, file I/O, and error handling
  - Create NPCs by type (Orc, Bear, Squirrel)
  - Save and load dungeon state
  - Handle invalid types and file errors
  
- **NPC Tests**: Verify core NPC properties and behaviors
  - Distance calculations
  - Coordinate validation (0-500 range)
  - Type-specific attack rules

### Legacy Test Script

The original test script is still available:

```bash
./test.sh
```

This creates sample NPCs, saves them, runs a battle cycle, and verifies the output.

## Requirements

- C++17 or later
- CMake 3.10 or later
- GCC/Clang with C++ support
- Internet connection (for first build to fetch GoogleTest)