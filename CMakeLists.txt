cmake_minimum_required(VERSION 3.5)
set (CMAKE_CXX_STANDARD 11)

project(battle_city_demo)
include_directories(include)
add_subdirectory(../public/src public)

add_executable(battle_city_demo MACOSX_BUNDLE "src/battlecitydemo.cpp" "src/menu.cpp" "src/sound.cpp" "src/map.cpp" "src/tank.cpp" "src/Bullet.cpp" "src/wincondition.cpp" "src/Tools.cpp")
target_link_libraries(battle_city_demo fssimplewindow ysbitmap ysbitmapfont yssimplesound)

