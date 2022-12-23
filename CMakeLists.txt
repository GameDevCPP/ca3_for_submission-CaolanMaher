cmake_minimum_required(VERSION 3.9)
# Compiler flags
if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /EHsc" CACHE INTERNAL "" FORCE)
elseif(APPLE)
    message("hello apple")
    set(CMAKE_OSX_DEPLOYMENT_TARGET 10.9 CACHE STRING "")
endif()
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Games_Engineering)

#### setup Directories ####
#Main output directory
set(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
# Ouput all DLLs from all libs into main build folder
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

add_custom_target(copy_resources ALL COMMAND ${CMAKE_COMMAND}
        -E copy_directory
        "${PROJECT_SOURCE_DIR}/res"
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIGURATION>/res
        )

#### Add External Dependencies ####
# SFML - graphics library
add_subdirectory("lib/sfml" EXCLUDE_FROM_ALL)
#include_directories("lib/sfml/include")
set(SFML_INCS "lib/sfml/include")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")

# B2D - Box2D phyics library
add_subdirectory("lib/b2d/Box2D" EXCLUDE_FROM_ALL)
#include_directories("lib/b2d/Box2D/")
set(B2D_INCS "lib/b2d/Box2D/")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")

#### Add Engine and our own library projects####

file(GLOB_RECURSE RESOURCE_FILES "res/*.*")
####
file(GLOB_RECURSE SOURCE_FILES engine/*.cpp engine/*.h)
add_library(lib_engine STATIC ${SOURCE_FILES} ${RESOURCE_FILES})
target_include_directories(lib_engine INTERFACE "${CMAKE_SOURCE_DIR}/engine/" PUBLIC SYSTEM ${B2D_INCS} )
target_link_libraries(lib_engine lib_tile_level_loader lib_maths lib_ecm Box2D sfml-graphics sfml-audio)

## Maths lib
add_library(lib_maths INTERFACE)
target_sources(lib_maths INTERFACE "${CMAKE_SOURCE_DIR}/lib_maths/maths.h")
target_include_directories(lib_maths INTERFACE "${CMAKE_SOURCE_DIR}/lib_maths" INTERFACE ${SFML_INCS})

## JSON lib
add_library(json INTERFACE)
target_sources(json INTERFACE "${CMAKE_SOURCE_DIR}json/json.h")
target_include_directories(json INTERFACE "${CMAKE_SOURCE_DIR}/json" INTERFACE ${SFML_INCS})

## Sound lib
add_library(lib_sound INTERFACE lib_sound/sound.h lib_sound/sound.cpp)
target_sources(lib_sound INTERFACE "${CMAKE_SOURCE_DIR}lib_sound/sound.h")
target_include_directories(lib_sound INTERFACE "${CMAKE_SOURCE_DIR}/lib_sound" INTERFACE ${SFML_INCS})

# Image lib
file(GLOB_RECURSE SOURCE_FILES lib_image/*.cpp lib_image/*.h)
add_library(lib_image STATIC ${SOURCE_FILES} ${RESOURCE_FILES} lib_image/image.cpp lib_image/image.h)
target_include_directories(lib_image INTERFACE "${CMAKE_SOURCE_DIR}/lib_image/" )
target_link_libraries(lib_image lib_maths sfml-graphics)

## Tile loader lib
file(GLOB_RECURSE SOURCE_FILES lib_tile_level_loader/*.cpp lib_tile_level_loader/*.h)
add_library(lib_tile_level_loader STATIC ${SOURCE_FILES} ${RESOURCE_FILES} lib_tile_level_loader/LevelSystem.cpp lib_tile_level_loader/LevelSystem.h)
target_include_directories(lib_tile_level_loader INTERFACE "${CMAKE_SOURCE_DIR}/lib_tile_level_loader/" )
target_link_libraries(lib_tile_level_loader lib_maths sfml-graphics)

## ECM lib
file(GLOB_RECURSE SOURCE_FILES lib_ecm/*.cpp lib_ecm/*.h)
add_library(lib_ecm STATIC ${SOURCE_FILES} json/json.h lib_image/image.h)
target_include_directories(lib_ecm INTERFACE "${CMAKE_SOURCE_DIR}/lib_ecm" )
target_link_libraries(lib_ecm PRIVATE lib_maths)

#### Add Practical Projects####

#@@@-

## 6 - Platformer
file(GLOB_RECURSE SOURCES lab_7_platformer/*.cpp practical_6_platformer/*.h)
file(GLOB_RECURSE CMPNTS lab_7_platformer/components/*.cpp practical_6_platformer/components/*.h)
file(GLOB_RECURSE SCENES lab_7_platformer/scenes/*.cpp practical_6_platformer/scenes/*.h)
#add_executable(PRACTICAL_7_PLATFORMER ${SOURCES} ${RESOURCE_FILES} lab_7_platformer/components/cmp_health_player.cpp lab_7_platformer/components/cmp_health_player.h lab_7_platformer/components/cmp_player_attack.cpp lab_7_platformer/components/cmp_player_attack.h)
#add_executable(PRACTICAL_7_PLATFORMER ${SOURCES} ${RESOURCE_FILES} lab_7_platformer/components/cmp_player_attack.cpp lab_7_platformer/components/cmp_player_attack.h)
add_executable(PRACTICAL_7_PLATFORMER ${SOURCES} ${RESOURCE_FILES} lab_7_platformer/components/cmp_health_player.cpp lab_7_platformer/components/cmp_health_player.h
        lab_7_platformer/scenes/scene_level4.cpp lab_7_platformer/scenes/scene_level4.h lab_7_platformer/components/cmp_player_attack.cpp lab_7_platformer/components/cmp_player_attack.h lab_7_platformer/components/cmp_item.cpp lab_7_platformer/components/cmp_item.h lab_7_platformer/components/cmp_double_jump.cpp lab_7_platformer/components/cmp_double_jump.h lab_7_platformer/components/cmp_flying_enemy.cpp lab_7_platformer/components/cmp_flying_enemy.h)
#add_executable(PRACTICAL_7_PLATFORMER ${SOURCES} ${RESOURCE_FILES})
source_group("components" FILES ${CMPNTS})
source_group("resources" FILES ${RESOURCE_FILES})
#target_include_directories(PRACTICAL_6_PLATFORMER SYSTEM PRIVATE ${SFML_INCS} ${B2D_INCS})
target_link_libraries(PRACTICAL_7_PLATFORMER lib_engine)
set(EXECUTABLES ${EXECUTABLES} PRACTICAL_7_PLATFORMER)

add_dependencies(PRACTICAL_7_PLATFORMER copy_resources)

set_target_properties(PRACTICAL_7_PLATFORMER
        PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
        )

foreach(exe ${EXECUTABLES})
    set_target_properties(${exe} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
            RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
            )
    #add all SFML dlls to the output directory
    add_custom_command(TARGET ${exe} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_BINARY_DIR}/lib/sfml/bin/"
            $<TARGET_FILE_DIR:${exe}>)
endforeach()

#@@@-