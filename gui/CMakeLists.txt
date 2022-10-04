cmake_minimum_required(VERSION 3.0.0)
project(gui VERSION 0.1.0)

include(CTest)
enable_testing()

file(GLOB GUI_HEADERS ./*.h)
file(GLOB GUI_SOURCES ./*.c)

add_library(gui STATIC ${GUI_SOURCES} ${GUI_HEADERS})

#C11
set_property(TARGET gui PROPERTY C_STANDARD 11)