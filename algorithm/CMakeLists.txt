cmake_minimum_required(VERSION 3.0.0)
project(algorithm VERSION 0.1.0)

include(CTest)
enable_testing()

file(GLOB GUI_HEADERS ./*.h)
file(GLOB GUI_SOURCES ./*.c)

add_library(algorithm STATIC ${GUI_SOURCES} ${GUI_HEADERS})

#C11
set_property(TARGET algorithm PROPERTY C_STANDARD 11)