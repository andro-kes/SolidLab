#pragma once

#include "NPC.h"

class Bear : public NPC {
public:
    Bear(const std::string& name, int x, int y);
    
    std::string getType() const override { return "Bear"; }
    void accept(BattleVisitor& visitor) override;
    bool canKill(const NPC& other) const override;
};
