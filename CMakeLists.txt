cmake_minimum_required (VERSION 3.10)

project ("ACP_Ray2_Multiplayer" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add ENet as a dependency
find_path(ENET_INCLUDE_DIR
    NAMES enet/enet.h
)
find_library(ENET_LIBRARY
    NAMES enet
)

# Collect all source files in src/
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)

# Build as DLL
add_library("ACP_Ray2_Multiplayer" SHARED ${SOURCES})

# Include dependencies and sources
target_include_directories(ACP_Ray2_Multiplayer PRIVATE
    src
    ${ENET_INCLUDE_DIR}
    "$ENV{acplib}/include"
)

target_link_directories(ACP_Ray2_Multiplayer PRIVATE
    "$ENV{acplib}/lib"
)

target_link_libraries(ACP_Ray2_Multiplayer PRIVATE
    ${ENET_LIBRARY}
    ACP_Ray2
    ws2_32
    winmm
)

# Copy mod to game directory
add_custom_command(TARGET ACP_Ray2_Multiplayer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:ACP_Ray2_Multiplayer>
        "$ENV{rayman2}/"
)