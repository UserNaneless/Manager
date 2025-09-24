cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

project(Bluetooth VERSION 0.1)


find_package(Qt6 COMPONENTS Core Widgets Bluetooth DBus Gui REQUIRED)

file(GLOB_RECURSE SFILES src/*.cpp)
file(GLOB_RECURSE HFILES include/*.h)
add_executable(Bluetooth ${SFILES} ${HFILES})

target_include_directories(Bluetooth PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(Bluetooth PRIVATE 
    Qt6::Core
    Qt6::Widgets
    Qt6::Bluetooth
    Qt6::DBus
    Qt6::Gui
)

