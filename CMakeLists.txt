cmake_minimum_required(VERSION 3.17)
project(UTEBackend)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE UTESrc "Backend/*.cpp" "Backend/*.hpp")

add_executable(UTEBackend main.cpp ${UTESrc} Backend/Backend.cpp Backend/Util.hpp)
set_target_properties(PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(UTEBackend )