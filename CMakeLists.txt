cmake_minimum_required(VERSION 3.10)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

# Set SFML_DIR to the correct path
set(SFML_DIR "C:/Libraries/SFML-2.6.0/lib/cmake/SFML")
set(CMAKE_BUILD_TYPE Release)  # Force release build

# Find SFML package
find_package(SFML 2 REQUIRED COMPONENTS graphics window system)

# Include SFML headers
include_directories(${SFML_INCLUDE_DIR})
include_directories("C:/Libraries/SFML-2.6.0/include")

link_directories("C:/Libraries/SFML-2.6.0/lib")


# Create executable
add_executable(untitled main.cpp
        GameBoard/Board.cpp
        Constants/BoardConstants.h
        GameBoard/Board.h
        AI/AI.cpp
        AI/AI.h
        GameBoard/BoardFactory.cpp
        GameBoard/BoardFactory.h
)

# Link SFML libraries
target_link_libraries(untitled
        sfml-graphics
        sfml-window
        sfml-system
)
