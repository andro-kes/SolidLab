#pragma once

#include "NPC.h"
#include "Orc.h"
#include "Bear.h"
#include "Squirrel.h"
#include <memory>
#include <string>
#include <fstream>
#include <vector>

// Factory pattern for NPC creation
class NPCFactory {
public:
    static std::shared_ptr<NPC> createNPC(const std::string& type, const std::string& name, int x, int y);
    
    static void saveToFile(const std::string& filename, const std::vector<NPCPtr>& npcs);
    static std::vector<NPCPtr> loadFromFile(const std::string& filename);
};
