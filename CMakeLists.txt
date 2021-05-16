cmake_minimum_required(VERSION 3.17)
project(UTEBackend)

set(CMAKE_CXX_STANDARD 17)

include_directories(Backend)

file(GLOB_RECURSE UTESrc "Backend/*.cpp" "Backend/*.hpp" "Backend/*.c" "Backend/*.h")

add_executable(UTEBackend ${UTESrc} main.cpp)
set_target_properties(PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(UTEBackend util)