# Design Patterns Implementation

This document explains how the three design patterns are implemented in the Dungeon Editor.

## Factory Pattern

**Location**: `NPCFactory` class in `include/NPCFactory.h` and `src/NPCFactory.cpp`

**Purpose**: Encapsulates the creation of NPC objects and provides file I/O functionality.

**Implementation**:
```cpp
class NPCFactory {
public:
    // Creates NPC instances based on type string
    static std::shared_ptr<NPC> createNPC(const std::string& type, 
                                          const std::string& name, 
                                          int x, int y);
    
    // Serialization
    static void saveToFile(const std::string& filename, 
                          const std::vector<NPCPtr>& npcs);
    
    // Deserialization
    static std::vector<NPCPtr> loadFromFile(const std::string& filename);
};
```

**Benefits**:
- Centralizes NPC creation logic
- Makes it easy to add new NPC types
- Handles file format parsing in one place
- Returns smart pointers for automatic memory management

**Usage Example**:
```cpp
// Create an NPC
auto orc = NPCFactory::createNPC("Orc", "Grom", 100, 100);

// Save dungeon state
NPCFactory::saveToFile("dungeon.txt", npcs);

// Load dungeon state
auto npcs = NPCFactory::loadFromFile("dungeon.txt");
```

## Visitor Pattern

**Location**: `BattleVisitor` class in `include/BattleVisitor.h` and `src/BattleVisitor.cpp`

**Purpose**: Implements the battle logic by visiting each NPC and processing combat.

**Implementation**:
```cpp
class BattleVisitor {
public:
    void visit(Orc& orc);
    void visit(Bear& bear);
    void visit(Squirrel& squirrel);
    
    void processBattle(NPC& attacker);
    void removeDefeated();
};

// Each NPC accepts the visitor
class NPC {
    virtual void accept(BattleVisitor& visitor) = 0;
};

class Orc : public NPC {
    void accept(BattleVisitor& visitor) override {
        visitor.visit(*this);
    }
};
```

**Benefits**:
- Separates battle logic from NPC classes
- Makes it easy to modify combat rules
- Allows different visitor implementations for different behaviors
- Double dispatch pattern (virtual accept + overloaded visit)

**Battle Flow**:
1. For each NPC in dungeon, call `accept(visitor)`
2. NPC calls appropriate `visit()` method on visitor
3. Visitor checks range and applies combat rules
4. Defeated NPCs are marked for removal
5. `removeDefeated()` removes all marked NPCs

**Usage Example**:
```cpp
BattleVisitor visitor(npcs);

// Each NPC accepts the visitor
for (auto& npc : npcs) {
    npc->accept(visitor);
}

// Remove defeated NPCs
visitor.removeDefeated();
```

## Observer Pattern

**Location**: `Observer.h` and `Observer.cpp` with `IObserver`, `ConsoleObserver`, `FileObserver`, and `ObserverManager`

**Purpose**: Notifies multiple observers about battle events for logging and display.

**Implementation**:
```cpp
// Observer interface
class IObserver {
public:
    virtual void onBattle(const NPC& attacker, 
                         const NPC& victim, 
                         bool killed) = 0;
};

// Concrete observers
class ConsoleObserver : public IObserver {
    void onBattle(...) override {
        std::cout << "Battle event...\n";
    }
};

class FileObserver : public IObserver {
    void onBattle(...) override {
        logFile << "Battle event...\n";
    }
};

// Observer manager (Subject)
class ObserverManager {
    static std::vector<ObserverPtr> observers;
public:
    static void addObserver(ObserverPtr observer);
    static void notifyBattle(const NPC& attacker, 
                            const NPC& victim, 
                            bool killed);
};
```

**Benefits**:
- Decouples battle system from logging/display
- Easy to add new observers without modifying battle code
- Multiple observers can react to the same event
- Clean separation of concerns

**Usage Example**:
```cpp
// Setup observers at startup
ObserverManager::addObserver(std::make_shared<ConsoleObserver>());
ObserverManager::addObserver(std::make_shared<FileObserver>("log.txt"));

// In battle code, notify all observers
ObserverManager::notifyBattle(attacker, victim, true);
```

## Pattern Interaction

The three patterns work together:

1. **Factory** creates NPCs with smart pointers
2. **Visitor** processes battle logic for each NPC
3. **Observer** gets notified when battles occur

**Flow**:
```
User adds NPC → Factory creates NPC → Store in vector
User triggers battle → Visitor visits each NPC → Checks combat rules
Combat occurs → Observer notified → Console/File logging
Defeated NPCs → Visitor removes them → Updated dungeon state
```

## Smart Pointers Usage

The implementation uses `std::shared_ptr<NPC>` throughout:

- **Factory**: Returns `shared_ptr` for automatic memory management
- **Storage**: NPCs stored in `std::vector<NPCPtr>` 
- **Observers**: Stored as `std::vector<ObserverPtr>`

**Benefits**:
- No manual memory management (no new/delete)
- Automatic cleanup when NPCs are removed
- Safe sharing of NPC references
- Exception-safe code

## SOLID Principles

The design follows SOLID principles:

- **S** - Single Responsibility: Each class has one clear purpose
- **O** - Open/Closed: Easy to add new NPC types via Factory
- **L** - Liskov Substitution: All NPCs can be used interchangeably
- **I** - Interface Segregation: Clean, focused interfaces (IObserver)
- **D** - Dependency Inversion: Code depends on abstractions (NPC base class)

## Adding New NPCs

To add a new NPC type (e.g., Dragon):

1. Create `Dragon.h` and `Dragon.cpp` inheriting from `NPC`
2. Implement `getType()`, `accept()`, and `canKill()`
3. Add case to `NPCFactory::createNPC()`
4. Add case to `NPC::load()`
5. No changes needed to Visitor or Observer!

This demonstrates the extensibility of the design.
