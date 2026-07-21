cmake_minimum_required (VERSION 3.10)

project ("ACP_Ray2_Multiplayer" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add ENet and libjuice as dependencies
find_path(ENET_INCLUDE_DIR NAMES enet/enet.h)
find_path(LIBJUICE_INCLUDE_DIR NAMES juice/juice.h)
find_library(ENET_LIBRARY NAMES enet)
find_library(LIBJUICE_LIBRARY NAMES juice)

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
    ${LIBJUICE_INCLUDE_DIR}
    "$ENV{acplib}/include"
    "$ENV{r2console}/src"
)

target_link_directories(ACP_Ray2_Multiplayer PRIVATE
    "$ENV{acplib}/lib"
    "$ENV{r2console}/Release"
)

target_link_libraries(ACP_Ray2_Multiplayer PRIVATE
    ${ENET_LIBRARY}
    ${LIBJUICE_LIBRARY}
    ACP_Ray2
    R2Console
    ws2_32
    winmm
)

# Copy mod to game directory
add_custom_command(TARGET ACP_Ray2_Multiplayer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:ACP_Ray2_Multiplayer>
        "$ENV{rayman2}/"
)