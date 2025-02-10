cmake_minimum_required(VERSION 3.10)
project(Oculto)

set(CMAKE_CXX_FLAGS "/W4 /EHsc")

include_directories(./headers/)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

add_executable(Oculto
"src/main.cpp"
)

target_link_libraries(Oculto PRIVATE sfml-system sfml-graphics sfml-window)