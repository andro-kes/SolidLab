#include "../include/NPCFactory.h"
#include <stdexcept>

std::shared_ptr<NPC> NPCFactory::createNPC(const std::string& type, const std::string& name, int x, int y) {
    if (type == "Orc") {
        return std::make_shared<Orc>(name, x, y);
    } else if (type == "Bear") {
        return std::make_shared<Bear>(name, x, y);
    } else if (type == "Squirrel") {
        return std::make_shared<Squirrel>(name, x, y);
    } else {
        throw std::invalid_argument("Unknown NPC type: " + type);
    }
}

void NPCFactory::saveToFile(const std::string& filename, const std::vector<NPCPtr>& npcs) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for writing: " + filename);
    }
    
    file << npcs.size() << "\n";
    for (const auto& npc : npcs) {
        npc->save(file);
    }
}

std::vector<NPCPtr> NPCFactory::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for reading: " + filename);
    }
    
    size_t count;
    file >> count;
    
    std::vector<NPCPtr> npcs;
    npcs.reserve(count);
    
    for (size_t i = 0; i < count; ++i) {
        auto npc = NPC::load(file);
        if (npc) {
            npcs.push_back(npc);
        }
    }
    
    return npcs;
}
