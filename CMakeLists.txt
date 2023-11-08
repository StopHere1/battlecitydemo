cmake_minimum_required(VERSION 3.5)

project(battle_city_demo)

if(APPLE)
    find_library(OPENGL_LIBRARY OpenGL)
    FIND_PATH(COCOA_INCLUDE_DIR Cocoa/Cocoa.h)
    find_library(COCOA_LIBRARY Cocoa)
endif(APPLE)

if(WIN32)
    find_library(OPENGL_LIBRARY OpenGL)
endif(WIN32)

if(LINUX)
    find_library(OPENGL_LIBRARY OpenGL)
endif(LINUX)

include_directories(include)
add_subdirectory(fssimplewindow_src)

add_executable(battle_city_demo MACOSX_BUNDLE "src/battlecitydemo.cpp" "src/menu.cpp")
target_link_libraries(battle_city_demo fssimplewindow)

if(APPLE)
    target_link_libraries(battle_city_demo ${COCOA_LIBRARY})
    target_link_libraries(battle_city_demo ${OPENGL_LIBRARY})
endif(APPLE)

if(WIN32)
    target_link_libraries(battle_city_demo ${OPENGL_LIBRARY})
endif(WIN32)

if(LINUX)
    target_link_libraries(battle_city_demo ${OPENGL_LIBRARY})
endif(LINUX)
