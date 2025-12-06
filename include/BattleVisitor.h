#pragma once

#include "NPC.h"
#include <vector>
#include <memory>

class Orc;
class Bear;
class Squirrel;

// Visitor pattern for battle
class BattleVisitor {
private:
    std::vector<NPCPtr>& npcs;
    std::vector<NPCPtr> toRemove;
    
public:
    explicit BattleVisitor(std::vector<NPCPtr>& npcs);
    
    void visit(Orc& orc);
    void visit(Bear& bear);
    void visit(Squirrel& squirrel);
    
    void processBattle(NPC& attacker);
    void removeDefeated();
    
private:
    void notifyKill(const NPC& attacker, const NPC& victim);
};
