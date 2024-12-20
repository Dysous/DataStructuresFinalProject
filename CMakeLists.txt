cmake_minimum_required(VERSION 3.9)

project(Jingle_Ballers)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lmingw32")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

add_executable(Jingle_Ballers main.cpp
        SDL_Plotter.cpp
        SDL_Plotter.h
        display.h
        bigText.h
        Red_Black_Tree.h
        fullsizeAssets.h
        fullsizeAssets.cpp
)
target_link_libraries(Jingle_Ballers SDL2main SDL2 SDL2_mixer)