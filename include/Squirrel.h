#pragma once

#include "NPC.h"

class Squirrel : public NPC {
public:
    Squirrel(const std::string& name, int x, int y);
    
    std::string getType() const override { return "Squirrel"; }
    void accept(BattleVisitor& visitor) override;
    bool canKill(const NPC& other) const override;
};
