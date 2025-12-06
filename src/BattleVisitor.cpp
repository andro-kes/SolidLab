#include "../include/BattleVisitor.h"
#include "../include/Observer.h"
#include "../include/Orc.h"
#include "../include/Bear.h"
#include "../include/Squirrel.h"
#include <algorithm>

BattleVisitor::BattleVisitor(std::vector<NPCPtr>& npcs) 
    : npcs(npcs) {}

void BattleVisitor::visit(Orc& orc) {
    processBattle(orc);
}

void BattleVisitor::visit(Bear& bear) {
    processBattle(bear);
}

void BattleVisitor::visit(Squirrel& squirrel) {
    processBattle(squirrel);
}

void BattleVisitor::processBattle(NPC& attacker) {
    const double BATTLE_RANGE = 100.0;
    
    for (const auto& defender : npcs) {
        if (&attacker == defender.get()) {
            continue; // Skip self
        }
        
        if (attacker.distanceTo(*defender) <= BATTLE_RANGE) {
            if (attacker.canKill(*defender)) {
                notifyKill(attacker, *defender);
                toRemove.push_back(defender);
            }
        }
    }
}

void BattleVisitor::removeDefeated() {
    for (const auto& victim : toRemove) {
        npcs.erase(
            std::remove_if(npcs.begin(), npcs.end(),
                [&victim](const NPCPtr& npc) { return npc == victim; }),
            npcs.end()
        );
    }
    toRemove.clear();
}

void BattleVisitor::notifyKill(const NPC& attacker, const NPC& victim) {
    ObserverManager::notifyBattle(attacker, victim, true);
}
