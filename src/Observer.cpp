#include "../include/Observer.h"
#include "../include/NPC.h"
#include <iostream>

// Static member initialization
std::vector<ObserverPtr> ObserverManager::observers;

// Console Observer
void ConsoleObserver::onBattle(const NPC& attacker, const NPC& victim, bool killed) {
    if (killed) {
        std::cout << "[BATTLE] " << attacker.getType() << " '" << attacker.getName() 
                  << "' killed " << victim.getType() << " '" << victim.getName() 
                  << "' at (" << victim.getX() << ", " << victim.getY() << ")\n";
    }
}

// File Observer
FileObserver::FileObserver(const std::string& filename) {
    logFile.open(filename, std::ios::app);
    if (!logFile.is_open()) {
        throw std::runtime_error("Cannot open log file: " + filename);
    }
}

FileObserver::~FileObserver() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

void FileObserver::onBattle(const NPC& attacker, const NPC& victim, bool killed) {
    if (killed && logFile.is_open()) {
        logFile << "[BATTLE] " << attacker.getType() << " '" << attacker.getName() 
                << "' killed " << victim.getType() << " '" << victim.getName() 
                << "' at (" << victim.getX() << ", " << victim.getY() << ")\n";
        logFile.flush();
    }
}

// Observer Manager
void ObserverManager::addObserver(ObserverPtr observer) {
    observers.push_back(observer);
}

void ObserverManager::notifyBattle(const NPC& attacker, const NPC& victim, bool killed) {
    for (auto& observer : observers) {
        observer->onBattle(attacker, victim, killed);
    }
}

void ObserverManager::clearObservers() {
    observers.clear();
}
