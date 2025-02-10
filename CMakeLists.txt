cmake_minimum_required(VERSION 3.10)
project(Oculto)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "/W4 /EHsc")

include_directories(./Headers/Engines)

find_package(SFML COMPONENTS Graphics Window System CONFIG REQUIRED)

add_executable(Oculto
"src/main.cpp"
 "src/Engines/DrawingEngine.cpp")

target_link_libraries(Oculto PRIVATE SFML::Graphics SFML::Window SFML::System)