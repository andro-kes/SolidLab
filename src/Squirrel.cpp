#include "../include/Squirrel.h"
#include "../include/BattleVisitor.h"

Squirrel::Squirrel(const std::string& name, int x, int y) 
    : NPC(name, x, y) {}

void Squirrel::accept(BattleVisitor& visitor) {
    visitor.visit(*this);
}

bool Squirrel::canKill(const NPC& /* other */) const {
    // Squirrel doesn't attack
    return false;
}
