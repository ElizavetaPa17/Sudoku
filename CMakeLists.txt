cmake_minimum_required(VERSION 3.7)

project(Sudoku 
        VERSION 1.0
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(SourceList "source/main.cpp"
               "source/resources/InitExitManager.cpp"
               "source/handle_elements/STimer.cpp"
               "source/renderer/STexture.cpp"
    )

#add_compile_options(-fsanitize=address -g -lpthread -static-libasn)
#add_link_options(-fsanitize=address)

add_executable(SudokuMain source/main.cpp ${SourceList})
target_link_libraries(SudokuMain 
                      PRIVATE  ${SDL_LIBRARIES} -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer)
add_definitions(-DSDL_MAIN_HANDLED)
