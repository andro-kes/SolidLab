#include "Bear.h"
#include "BattleVisitor.h"

Bear::Bear(const std::string& name, int x, int y) 
    : NPC(name, x, y) {}

void Bear::accept(BattleVisitor& visitor) {
    visitor.visit(*this);
}

bool Bear::canKill(const NPC& other) const {
    // Bear kills squirrels
    return other.getType() == "Squirrel";
}
