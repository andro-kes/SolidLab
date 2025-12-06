#include <gtest/gtest.h>
#include "../include/NPCFactory.h"
#include "../include/Orc.h"
#include "../include/Bear.h"
#include "../include/Squirrel.h"
#include <fstream>
#include <cstdio>
#include <filesystem>
#include <random>

// Test fixture for NPCFactory tests
class NPCFactoryTest : public ::testing::Test {
protected:
    std::string testFile;
    
    void SetUp() override {
        // Generate unique temp file path
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(10000, 99999);
        std::string filename = "test_npc_factory_" + std::to_string(dis(gen)) + ".txt";
        testFile = (std::filesystem::temp_directory_path() / filename).string();
    }
    
    void TearDown() override {
        // Clean up test file
        std::filesystem::remove(testFile);
    }
};

// Test: Create Orc via factory
TEST_F(NPCFactoryTest, CreateOrc) {
    auto npc = NPCFactory::createNPC("Orc", "Grom", 100, 100);
    
    ASSERT_NE(npc, nullptr);
    EXPECT_EQ(npc->getType(), "Orc");
    EXPECT_EQ(npc->getName(), "Grom");
    EXPECT_EQ(npc->getX(), 100);
    EXPECT_EQ(npc->getY(), 100);
}

// Test: Create Bear via factory
TEST_F(NPCFactoryTest, CreateBear) {
    auto npc = NPCFactory::createNPC("Bear", "Bruno", 200, 150);
    
    ASSERT_NE(npc, nullptr);
    EXPECT_EQ(npc->getType(), "Bear");
    EXPECT_EQ(npc->getName(), "Bruno");
    EXPECT_EQ(npc->getX(), 200);
    EXPECT_EQ(npc->getY(), 150);
}

// Test: Create Squirrel via factory
TEST_F(NPCFactoryTest, CreateSquirrel) {
    auto npc = NPCFactory::createNPC("Squirrel", "Chip", 300, 250);
    
    ASSERT_NE(npc, nullptr);
    EXPECT_EQ(npc->getType(), "Squirrel");
    EXPECT_EQ(npc->getName(), "Chip");
    EXPECT_EQ(npc->getX(), 300);
    EXPECT_EQ(npc->getY(), 250);
}

// Test: Invalid NPC type throws exception
TEST_F(NPCFactoryTest, InvalidTypeThrowsException) {
    EXPECT_THROW(
        NPCFactory::createNPC("Dragon", "Smaug", 100, 100),
        std::invalid_argument
    );
}

// Test: Save NPCs to file
TEST_F(NPCFactoryTest, SaveToFile) {
    std::vector<NPCPtr> npcs;
    npcs.push_back(std::make_shared<Orc>("Grom", 100, 100));
    npcs.push_back(std::make_shared<Bear>("Bruno", 200, 150));
    npcs.push_back(std::make_shared<Squirrel>("Chip", 300, 250));
    
    NPCFactory::saveToFile(testFile, npcs);
    
    // Verify file exists and has content
    std::ifstream file(testFile);
    ASSERT_TRUE(file.is_open());
    
    size_t count;
    file >> count;
    EXPECT_EQ(count, 3);
    
    std::string type, name;
    int x, y;
    
    // Check first NPC
    file >> type >> name >> x >> y;
    EXPECT_EQ(type, "Orc");
    EXPECT_EQ(name, "Grom");
    EXPECT_EQ(x, 100);
    EXPECT_EQ(y, 100);
    
    // Check second NPC
    file >> type >> name >> x >> y;
    EXPECT_EQ(type, "Bear");
    EXPECT_EQ(name, "Bruno");
    EXPECT_EQ(x, 200);
    EXPECT_EQ(y, 150);
    
    // Check third NPC
    file >> type >> name >> x >> y;
    EXPECT_EQ(type, "Squirrel");
    EXPECT_EQ(name, "Chip");
    EXPECT_EQ(x, 300);
    EXPECT_EQ(y, 250);
}

// Test: Load NPCs from file
TEST_F(NPCFactoryTest, LoadFromFile) {
    // Create test file
    {
        std::ofstream file(testFile);
        file << "3\n";
        file << "Orc Grom 100 100\n";
        file << "Bear Bruno 200 150\n";
        file << "Squirrel Chip 300 250\n";
    }
    
    auto npcs = NPCFactory::loadFromFile(testFile);
    
    ASSERT_EQ(npcs.size(), 3);
    
    // Check first NPC
    EXPECT_EQ(npcs[0]->getType(), "Orc");
    EXPECT_EQ(npcs[0]->getName(), "Grom");
    EXPECT_EQ(npcs[0]->getX(), 100);
    EXPECT_EQ(npcs[0]->getY(), 100);
    
    // Check second NPC
    EXPECT_EQ(npcs[1]->getType(), "Bear");
    EXPECT_EQ(npcs[1]->getName(), "Bruno");
    EXPECT_EQ(npcs[1]->getX(), 200);
    EXPECT_EQ(npcs[1]->getY(), 150);
    
    // Check third NPC
    EXPECT_EQ(npcs[2]->getType(), "Squirrel");
    EXPECT_EQ(npcs[2]->getName(), "Chip");
    EXPECT_EQ(npcs[2]->getX(), 300);
    EXPECT_EQ(npcs[2]->getY(), 250);
}

// Test: Save and load round-trip
TEST_F(NPCFactoryTest, SaveLoadRoundTrip) {
    std::vector<NPCPtr> originalNpcs;
    originalNpcs.push_back(std::make_shared<Orc>("Grom", 100, 100));
    originalNpcs.push_back(std::make_shared<Bear>("Bruno", 200, 150));
    originalNpcs.push_back(std::make_shared<Squirrel>("Chip", 300, 250));
    
    NPCFactory::saveToFile(testFile, originalNpcs);
    auto loadedNpcs = NPCFactory::loadFromFile(testFile);
    
    ASSERT_EQ(loadedNpcs.size(), originalNpcs.size());
    
    for (size_t i = 0; i < originalNpcs.size(); ++i) {
        EXPECT_EQ(loadedNpcs[i]->getType(), originalNpcs[i]->getType());
        EXPECT_EQ(loadedNpcs[i]->getName(), originalNpcs[i]->getName());
        EXPECT_EQ(loadedNpcs[i]->getX(), originalNpcs[i]->getX());
        EXPECT_EQ(loadedNpcs[i]->getY(), originalNpcs[i]->getY());
    }
}

// Test: Load empty file
TEST_F(NPCFactoryTest, LoadEmptyFile) {
    {
        std::ofstream file(testFile);
        file << "0\n";
    }
    
    auto npcs = NPCFactory::loadFromFile(testFile);
    EXPECT_EQ(npcs.size(), 0);
}

// Test: Load file with invalid NPC type (should skip invalid entries)
TEST_F(NPCFactoryTest, LoadFileWithInvalidType) {
    {
        std::ofstream file(testFile);
        file << "3\n";
        file << "Orc Grom 100 100\n";
        file << "Dragon Smaug 200 150\n";  // Invalid type
        file << "Bear Bruno 300 250\n";
    }
    
    auto npcs = NPCFactory::loadFromFile(testFile);
    
    // Should load 2 valid NPCs, skip the invalid one
    ASSERT_EQ(npcs.size(), 2);
    EXPECT_EQ(npcs[0]->getType(), "Orc");
    EXPECT_EQ(npcs[1]->getType(), "Bear");
}

// Test: Load from non-existent file throws exception
TEST_F(NPCFactoryTest, LoadNonExistentFileThrows) {
    std::string nonexistentFile = (std::filesystem::temp_directory_path() / "nonexistent_file_xyz_12345.txt").string();
    EXPECT_THROW(
        NPCFactory::loadFromFile(nonexistentFile),
        std::runtime_error
    );
}

// Test: Save to invalid path throws exception
TEST_F(NPCFactoryTest, SaveToInvalidPathThrows) {
    std::vector<NPCPtr> npcs;
    npcs.push_back(std::make_shared<Orc>("Grom", 100, 100));
    
    // Use a deeply nested non-existent directory path
    std::string invalidPath = (std::filesystem::temp_directory_path() / "nonexistent_dir_xyz" / "subdir" / "test.txt").string();
    EXPECT_THROW(
        NPCFactory::saveToFile(invalidPath, npcs),
        std::runtime_error
    );
}
