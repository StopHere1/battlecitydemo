cmake_minimum_required(VERSION 3.5)

project(battle_city_demo)
include_directories(include)
add_subdirectory(../public/src public)

add_executable(battle_city_demo MACOSX_BUNDLE "src/battlecitydemo.cpp" "src/menu.cpp" "src/sound.cpp" )
target_link_libraries(battle_city_demo fssimplewindow ysbitmap ysbitmapfont yssimplesound)

