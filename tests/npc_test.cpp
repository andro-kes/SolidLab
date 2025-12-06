#include <gtest/gtest.h>
#include "../include/NPC.h"
#include "../include/Orc.h"
#include "../include/Bear.h"
#include "../include/Squirrel.h"
#include <cmath>

// Test: Distance calculation between NPCs
TEST(NPCTest, DistanceCalculation) {
    auto orc = std::make_shared<Orc>("Grom", 0, 0);
    auto bear = std::make_shared<Bear>("Bruno", 3, 4);
    
    double distance = orc->distanceTo(*bear);
    EXPECT_DOUBLE_EQ(distance, 5.0);
}

// Test: Distance to self is zero
TEST(NPCTest, DistanceToSelfIsZero) {
    auto orc = std::make_shared<Orc>("Grom", 100, 100);
    
    double distance = orc->distanceTo(*orc);
    EXPECT_DOUBLE_EQ(distance, 0.0);
}

// Test: Distance calculation with negative delta
TEST(NPCTest, DistanceWithNegativeDelta) {
    auto orc = std::make_shared<Orc>("Grom", 100, 100);
    auto bear = std::make_shared<Bear>("Bruno", 50, 50);
    
    double distance = orc->distanceTo(*bear);
    double expected = std::sqrt(50*50 + 50*50);
    EXPECT_DOUBLE_EQ(distance, expected);
}

// Test: Orc properties
TEST(NPCTest, OrcProperties) {
    auto orc = std::make_shared<Orc>("Grom", 100, 150);
    
    EXPECT_EQ(orc->getType(), "Orc");
    EXPECT_EQ(orc->getName(), "Grom");
    EXPECT_EQ(orc->getX(), 100);
    EXPECT_EQ(orc->getY(), 150);
}

// Test: Bear properties
TEST(NPCTest, BearProperties) {
    auto bear = std::make_shared<Bear>("Bruno", 200, 250);
    
    EXPECT_EQ(bear->getType(), "Bear");
    EXPECT_EQ(bear->getName(), "Bruno");
    EXPECT_EQ(bear->getX(), 200);
    EXPECT_EQ(bear->getY(), 250);
}

// Test: Squirrel properties
TEST(NPCTest, SquirrelProperties) {
    auto squirrel = std::make_shared<Squirrel>("Chip", 300, 350);
    
    EXPECT_EQ(squirrel->getType(), "Squirrel");
    EXPECT_EQ(squirrel->getName(), "Chip");
    EXPECT_EQ(squirrel->getX(), 300);
    EXPECT_EQ(squirrel->getY(), 350);
}

// Test: Valid coordinates at minimum boundary
TEST(NPCTest, ValidCoordinatesMinBoundary) {
    EXPECT_NO_THROW({
        auto orc = std::make_shared<Orc>("Grom", 0, 0);
    });
}

// Test: Valid coordinates at maximum boundary
TEST(NPCTest, ValidCoordinatesMaxBoundary) {
    EXPECT_NO_THROW({
        auto orc = std::make_shared<Orc>("Grom", 500, 500);
    });
}

// Test: Invalid coordinates below minimum throws exception
TEST(NPCTest, InvalidCoordinatesBelowMin) {
    EXPECT_THROW({
        auto orc = std::make_shared<Orc>("Grom", -1, 100);
    }, std::invalid_argument);
    
    EXPECT_THROW({
        auto orc = std::make_shared<Orc>("Grom", 100, -1);
    }, std::invalid_argument);
}

// Test: Invalid coordinates above maximum throws exception
TEST(NPCTest, InvalidCoordinatesAboveMax) {
    EXPECT_THROW({
        auto orc = std::make_shared<Orc>("Grom", 501, 100);
    }, std::invalid_argument);
    
    EXPECT_THROW({
        auto orc = std::make_shared<Orc>("Grom", 100, 501);
    }, std::invalid_argument);
}

// Test: Orc canKill rules
TEST(NPCTest, OrcCanKillRules) {
    auto orc = std::make_shared<Orc>("Grom", 100, 100);
    auto targetOrc = std::make_shared<Orc>("Gruk", 110, 110);
    auto targetBear = std::make_shared<Bear>("Bruno", 120, 120);
    auto targetSquirrel = std::make_shared<Squirrel>("Chip", 130, 130);
    
    EXPECT_TRUE(orc->canKill(*targetOrc));
    EXPECT_TRUE(orc->canKill(*targetBear));
    EXPECT_FALSE(orc->canKill(*targetSquirrel));
}

// Test: Bear canKill rules
TEST(NPCTest, BearCanKillRules) {
    auto bear = std::make_shared<Bear>("Bruno", 100, 100);
    auto targetOrc = std::make_shared<Orc>("Grom", 110, 110);
    auto targetBear = std::make_shared<Bear>("Boris", 120, 120);
    auto targetSquirrel = std::make_shared<Squirrel>("Chip", 130, 130);
    
    EXPECT_FALSE(bear->canKill(*targetOrc));
    EXPECT_FALSE(bear->canKill(*targetBear));
    EXPECT_TRUE(bear->canKill(*targetSquirrel));
}

// Test: Squirrel canKill rules (doesn't attack)
TEST(NPCTest, SquirrelCanKillRules) {
    auto squirrel = std::make_shared<Squirrel>("Chip", 100, 100);
    auto targetOrc = std::make_shared<Orc>("Grom", 110, 110);
    auto targetBear = std::make_shared<Bear>("Bruno", 120, 120);
    auto targetSquirrel = std::make_shared<Squirrel>("Dale", 130, 130);
    
    EXPECT_FALSE(squirrel->canKill(*targetOrc));
    EXPECT_FALSE(squirrel->canKill(*targetBear));
    EXPECT_FALSE(squirrel->canKill(*targetSquirrel));
}
