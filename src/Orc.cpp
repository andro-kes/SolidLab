#include "Orc.h"
#include "BattleVisitor.h"

Orc::Orc(const std::string& name, int x, int y) 
    : NPC(name, x, y) {}

void Orc::accept(BattleVisitor& visitor) {
    visitor.visit(*this);
}

bool Orc::canKill(const NPC& other) const {
    // Orc kills orcs and bears
    std::string type = other.getType();
    return (type == "Orc" || type == "Bear");
}
