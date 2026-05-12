cmake_minimum_required(VERSION 3.10)
project(SFML_Project)

# SFML 3 requires C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Help CMake find Homebrew
list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew")

# 2. Try finding SFML 3 without specifying components first to see what's available
# Then call the specific components. Note the Capitalization.
find_package(SFML 3 REQUIRED COMPONENTS Audio Graphics Window System)

add_executable(sfmltest main.cpp)

# 3. Link the SFML libraries using the namespace targets
target_link_libraries(sfmltest 
    SFML::Audio 
    SFML::Graphics 
    SFML::Window 
    SFML::System
)