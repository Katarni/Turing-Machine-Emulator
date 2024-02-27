cmake_minimum_required(VERSION 3.27)
project(TuringMachine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(TuringMachine main.cpp
        src/App.cpp
        include/App.h
        include/header.h
        src/Turing.cpp
        include/Turing.h
)
target_link_libraries(TuringMachine
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

