cmake_minimum_required(VERSION 3.7)

project(Sudoku 
        VERSION 1.0
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(SourceList "${CMAKE_CURRENT_SOURCE_DIR}/source/widget/SApplication.cpp"
               "${CMAKE_CURRENT_SOURCE_DIR}/source/resources/InitExitManager.cpp"
               "${CMAKE_CURRENT_SOURCE_DIR}/source/handle_elements/STimer.cpp"
               "${CMAKE_CURRENT_SOURCE_DIR}/source/renderer/STexture.cpp"
               "${CMAKE_CURRENT_SOURCE_DIR}/source/renderer/SFont.cpp"
               "${CMAKE_CURRENT_SOURCE_DIR}/source/widget/SButton.cpp"
               "${CMAKE_CURRENT_SOURCE_DIR}/source/handle_elements/SBoard.cpp"
               "${CMAKE_CURRENT_SOURCE_DIR}/source/handle_elements/SLittleCell.cpp"
               "${CMAKE_CURRENT_SOURCE_DIR}/source/handle_elements/SCellFlyweight.cpp"
               "${CMAKE_CURRENT_SOURCE_DIR}/source/widget/SScoreLabel.cpp"
               "${CMAKE_CURRENT_SOURCE_DIR}/source/widget/STimerLabel.cpp"
    )

add_definitions(-DSDL_MAIN_HANDLED)

#add_compile_options(-fsanitize=address -g -lpthread -static-libasn)
#add_link_options(-fsanitize=address)

add_executable(SudokuMain "${CMAKE_CURRENT_SOURCE_DIR}/source/main.cpp" ${SourceList})
target_link_libraries(SudokuMain
                      PRIVATE  ${SDL_LIBRARIES} -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
                      )
