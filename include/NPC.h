#pragma once

#include <string>
#include <memory>
#include <iostream>

class BattleVisitor;

// Base NPC class
class NPC {
protected:
    std::string name;
    int x, y;

public:
    NPC(const std::string& name, int x, int y);
    virtual ~NPC() = default;

    virtual std::string getType() const = 0;
    virtual void accept(BattleVisitor& visitor) = 0;
    
    std::string getName() const { return name; }
    int getX() const { return x; }
    int getY() const { return y; }
    
    virtual bool canKill(const NPC& other) const = 0;
    
    double distanceTo(const NPC& other) const;
    
    virtual void save(std::ostream& os) const;
    static std::shared_ptr<NPC> load(std::istream& is);
};

using NPCPtr = std::shared_ptr<NPC>;
