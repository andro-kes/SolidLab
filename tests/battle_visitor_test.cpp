#include <gtest/gtest.h>
#include "../include/NPC.h"
#include "../include/Orc.h"
#include "../include/Bear.h"
#include "../include/Squirrel.h"
#include "../include/BattleVisitor.h"
#include <memory>
#include <vector>

// Test fixture for BattleVisitor tests
class BattleVisitorTest : public ::testing::Test {
protected:
    std::vector<NPCPtr> npcs;
    
    void SetUp() override {
        npcs.clear();
    }
    
    void TearDown() override {
        npcs.clear();
    }
};

// Test: Orc kills Orc within range
TEST_F(BattleVisitorTest, OrcKillsOrcWithinRange) {
    auto orc1 = std::make_shared<Orc>("Grom", 100, 100);
    auto orc2 = std::make_shared<Orc>("Gruk", 150, 100);
    
    npcs.push_back(orc1);
    npcs.push_back(orc2);
    
    BattleVisitor visitor(npcs);
    orc1->accept(visitor);
    visitor.removeDefeated();
    
    // orc2 should be killed (distance = 50, within 100 range)
    EXPECT_EQ(npcs.size(), 1);
    EXPECT_EQ(npcs[0]->getName(), "Grom");
}

// Test: Orc kills Bear within range
TEST_F(BattleVisitorTest, OrcKillsBearWithinRange) {
    auto orc = std::make_shared<Orc>("Grom", 100, 100);
    auto bear = std::make_shared<Bear>("Bruno", 150, 100);
    
    npcs.push_back(orc);
    npcs.push_back(bear);
    
    BattleVisitor visitor(npcs);
    orc->accept(visitor);
    visitor.removeDefeated();
    
    // Bear should be killed (distance = 50, within 100 range)
    EXPECT_EQ(npcs.size(), 1);
    EXPECT_EQ(npcs[0]->getName(), "Grom");
}

// Test: Orc doesn't kill Squirrel
TEST_F(BattleVisitorTest, OrcDoesNotKillSquirrel) {
    auto orc = std::make_shared<Orc>("Grom", 100, 100);
    auto squirrel = std::make_shared<Squirrel>("Chip", 110, 100);
    
    npcs.push_back(orc);
    npcs.push_back(squirrel);
    
    BattleVisitor visitor(npcs);
    orc->accept(visitor);
    visitor.removeDefeated();
    
    // Squirrel should survive (Orc doesn't attack Squirrels)
    EXPECT_EQ(npcs.size(), 2);
}

// Test: Bear kills Squirrel within range
TEST_F(BattleVisitorTest, BearKillsSquirrelWithinRange) {
    auto bear = std::make_shared<Bear>("Bruno", 100, 100);
    auto squirrel = std::make_shared<Squirrel>("Chip", 150, 100);
    
    npcs.push_back(bear);
    npcs.push_back(squirrel);
    
    BattleVisitor visitor(npcs);
    bear->accept(visitor);
    visitor.removeDefeated();
    
    // Squirrel should be killed (distance = 50, within 100 range)
    EXPECT_EQ(npcs.size(), 1);
    EXPECT_EQ(npcs[0]->getName(), "Bruno");
}

// Test: Bear doesn't kill Orc
TEST_F(BattleVisitorTest, BearDoesNotKillOrc) {
    auto bear = std::make_shared<Bear>("Bruno", 100, 100);
    auto orc = std::make_shared<Orc>("Grom", 110, 100);
    
    npcs.push_back(bear);
    npcs.push_back(orc);
    
    BattleVisitor visitor(npcs);
    bear->accept(visitor);
    visitor.removeDefeated();
    
    // Orc should survive (Bear doesn't attack Orcs)
    EXPECT_EQ(npcs.size(), 2);
}

// Test: Bear doesn't kill Bear
TEST_F(BattleVisitorTest, BearDoesNotKillBear) {
    auto bear1 = std::make_shared<Bear>("Bruno", 100, 100);
    auto bear2 = std::make_shared<Bear>("Boris", 110, 100);
    
    npcs.push_back(bear1);
    npcs.push_back(bear2);
    
    BattleVisitor visitor(npcs);
    bear1->accept(visitor);
    visitor.removeDefeated();
    
    // Both bears should survive
    EXPECT_EQ(npcs.size(), 2);
}

// Test: Squirrel doesn't attack anyone
TEST_F(BattleVisitorTest, SquirrelDoesNotAttack) {
    auto squirrel = std::make_shared<Squirrel>("Chip", 100, 100);
    auto orc = std::make_shared<Orc>("Grom", 110, 100);
    auto bear = std::make_shared<Bear>("Bruno", 120, 100);
    
    npcs.push_back(squirrel);
    npcs.push_back(orc);
    npcs.push_back(bear);
    
    BattleVisitor visitor(npcs);
    squirrel->accept(visitor);
    visitor.removeDefeated();
    
    // All NPCs should survive (Squirrel doesn't attack)
    EXPECT_EQ(npcs.size(), 3);
}

// Test: No attacks outside 100 unit range
TEST_F(BattleVisitorTest, NoAttackOutsideRange) {
    auto orc = std::make_shared<Orc>("Grom", 100, 100);
    auto bear = std::make_shared<Bear>("Bruno", 250, 100);
    
    npcs.push_back(orc);
    npcs.push_back(bear);
    
    BattleVisitor visitor(npcs);
    orc->accept(visitor);
    visitor.removeDefeated();
    
    // Bear should survive (distance = 150, outside 100 range)
    EXPECT_EQ(npcs.size(), 2);
}

// Test: Orc at exact 100 unit range kills Bear
TEST_F(BattleVisitorTest, OrcKillsBearAtExactRange) {
    auto orc = std::make_shared<Orc>("Grom", 100, 100);
    auto bear = std::make_shared<Bear>("Bruno", 200, 100);
    
    npcs.push_back(orc);
    npcs.push_back(bear);
    
    BattleVisitor visitor(npcs);
    orc->accept(visitor);
    visitor.removeDefeated();
    
    // Bear should be killed (distance = 100, within range)
    EXPECT_EQ(npcs.size(), 1);
    EXPECT_EQ(npcs[0]->getName(), "Grom");
}

// Test: Self-attack prevention
TEST_F(BattleVisitorTest, NpcDoesNotAttackSelf) {
    auto orc = std::make_shared<Orc>("Grom", 100, 100);
    
    npcs.push_back(orc);
    
    BattleVisitor visitor(npcs);
    orc->accept(visitor);
    visitor.removeDefeated();
    
    // Orc should survive (no self-attack)
    EXPECT_EQ(npcs.size(), 1);
}

// Test: Multiple targets in range
TEST_F(BattleVisitorTest, MultipleTargetsInRange) {
    auto orc = std::make_shared<Orc>("Grom", 100, 100);
    auto bear1 = std::make_shared<Bear>("Bruno", 120, 100);
    auto bear2 = std::make_shared<Bear>("Boris", 140, 100);
    auto orc2 = std::make_shared<Orc>("Gruk", 160, 100);
    
    npcs.push_back(orc);
    npcs.push_back(bear1);
    npcs.push_back(bear2);
    npcs.push_back(orc2);
    
    BattleVisitor visitor(npcs);
    orc->accept(visitor);
    visitor.removeDefeated();
    
    // All Bears and orc2 should be killed, only attacking orc survives
    EXPECT_EQ(npcs.size(), 1);
    EXPECT_EQ(npcs[0]->getName(), "Grom");
}

// Test: Battle with mixed NPCs, some in range, some not
TEST_F(BattleVisitorTest, MixedRangeScenario) {
    auto bear = std::make_shared<Bear>("Bruno", 100, 100);
    auto squirrel1 = std::make_shared<Squirrel>("Chip", 150, 100);  // In range
    auto squirrel2 = std::make_shared<Squirrel>("Dale", 250, 100);  // Out of range
    auto orc = std::make_shared<Orc>("Grom", 300, 100);  // Out of range
    
    npcs.push_back(bear);
    npcs.push_back(squirrel1);
    npcs.push_back(squirrel2);
    npcs.push_back(orc);
    
    BattleVisitor visitor(npcs);
    bear->accept(visitor);
    visitor.removeDefeated();
    
    // Only squirrel1 should be killed
    EXPECT_EQ(npcs.size(), 3);
    
    // Verify survivors
    bool foundSquirrel2 = false;
    bool foundOrc = false;
    bool foundBear = false;
    for (const auto& npc : npcs) {
        if (npc->getName() == "Dale") foundSquirrel2 = true;
        if (npc->getName() == "Grom") foundOrc = true;
        if (npc->getName() == "Bruno") foundBear = true;
    }
    EXPECT_TRUE(foundSquirrel2);
    EXPECT_TRUE(foundOrc);
    EXPECT_TRUE(foundBear);
}
