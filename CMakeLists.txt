cmake_minimum_required(VERSION 3.10)
project(DungeonEditor CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

include_directories(${CMAKE_SOURCE_DIR}/include)

# Main application executable
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

# Testing configuration
option(BUILD_TESTING "Build the testing tree" ON)

if(BUILD_TESTING)
    enable_testing()
    
    # Fetch GoogleTest
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    
    # Test executable
    add_executable(dungeon_tests
        tests/battle_visitor_test.cpp
        tests/npc_factory_test.cpp
        tests/npc_test.cpp
        src/NPC.cpp
        src/Orc.cpp
        src/Bear.cpp
        src/Squirrel.cpp
        src/NPCFactory.cpp
        src/BattleVisitor.cpp
        src/Observer.cpp
    )
    
    target_include_directories(dungeon_tests PRIVATE include)
    target_link_libraries(dungeon_tests GTest::gtest_main)
    
    # Register tests with CTest
    include(GoogleTest)
    gtest_discover_tests(dungeon_tests)
endif()
