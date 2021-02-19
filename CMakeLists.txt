cmake_minimum_required(VERSION 3.17)
project(UTE)

set(CMAKE_CXX_STANDARD 17)



add_executable()
set_target_properties(PROPERTIES LINKER_LANGUAGE CXX)

if(WIN32)
    target_link_libraries(UTE )
else()
    target_link_libraries(UTE )
endif()


add_executable()