cmake_minimum_required(VERSION 3.16)

project(SlotMachineGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.2
)

FetchContent_MakeAvailable(SFML)

add_executable(SlotMachineGame
    main.cpp
    abstractstate.h
    startstate.h startstate.cpp
    spinstate.h spinstate.cpp
    finishstate.h finishstate.cpp
    symbol.h symbol.cpp
    slotmachinegame.h slotmachinegame.cpp
    button.h button.cpp
    reel.h reel.cpp
    label.h label.cpp
    scorelabel.h scorelabel.cpp
)

target_link_libraries(SlotMachineGame PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)

if(WIN32)
    target_link_libraries(SlotMachineGame PRIVATE sfml-main)
endif()

if(UNIX AND NOT APPLE)
    find_package(X11 REQUIRED)
    target_link_libraries(SlotMachineGame PRIVATE X11)
endif()
