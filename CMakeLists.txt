cmake_minimum_required(VERSION 3.16)
project(BitLifeCPP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system QUIET)

# If SFML is not found, we'll use a fallback text-based version
if(NOT SFML_FOUND)
    message(STATUS "SFML not found. Falling back to text-based version.")
    message(STATUS "To use graphics, install SFML: https://www.sfml-dev.org/")
    add_compile_definitions(TEXT_MODE)
endif()

# Add nlohmann_json for save/load
find_package(nlohmann_json QUIET)
if(NOT nlohmann_json_FOUND)
    message(STATUS "nlohmann_json not found. Using header-only version.")
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/json)
endif()

add_executable(bitlife
    src/main.cpp
    src/Game.cpp
    src/UI.cpp
    src/SaveLoad.cpp
)

target_include_directories(bitlife PRIVATE include)

if(SFML_FOUND)
    target_link_libraries(bitlife PRIVATE sfml-graphics sfml-window sfml-system)
endif()

if(nlohmann_json_FOUND)
    target_link_libraries(bitlife PRIVATE nlohmann_json::nlohmann_json)
endif()
