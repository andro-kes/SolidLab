cmake_minimum_required(VERSION 3.10)
project(DungeonEditor CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(dungeon_editor
    src/main.cpp
    src/NPC.cpp
    src/Orc.cpp
    src/Bear.cpp
    src/Squirrel.cpp
    src/NPCFactory.cpp
    src/BattleVisitor.cpp
    src/Observer.cpp
)

target_include_directories(dungeon_editor PRIVATE include)
