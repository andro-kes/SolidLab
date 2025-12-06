#pragma once

#include <string>
#include <memory>
#include <vector>
#include <fstream>

class NPC;

// Observer interface
class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void onBattle(const NPC& attacker, const NPC& victim, bool killed) = 0;
};

using ObserverPtr = std::shared_ptr<IObserver>;

// Console observer
class ConsoleObserver : public IObserver {
public:
    void onBattle(const NPC& attacker, const NPC& victim, bool killed) override;
};

// File observer
class FileObserver : public IObserver {
private:
    std::ofstream logFile;
    
public:
    explicit FileObserver(const std::string& filename);
    ~FileObserver() override;
    
    void onBattle(const NPC& attacker, const NPC& victim, bool killed) override;
};

// Observer manager
class ObserverManager {
private:
    static std::vector<ObserverPtr> observers;
    
public:
    static void addObserver(ObserverPtr observer);
    static void notifyBattle(const NPC& attacker, const NPC& victim, bool killed);
    static void clearObservers();
};
