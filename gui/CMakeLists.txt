cmake_minimum_required(VERSION 3.0.0)
project(gui VERSION 0.1.0)

include(CTest)
enable_testing()

file(GLOB GUI_HEADERS ./*.h)
file(GLOB GUI_SOURCES ./*.c)

if(WIN32)
    set(SDL2_DIR "${CMAKE_CURRENT_LIST_DIR}/../sdl2-lib")
    set(SDL2_INCLUDE_DIRS "${SDL2_DIR}/include")
    set(SDL2_LIBRARIES "${SDL2_DIR}/lib/x86/SDL2.lib;${SDL2_DIR}/lib/x86/SDL2main.lib")
else()
    find_package(SDL2 REQUIRED)
endif()

#SDL2
include_directories(${SDL2_INCLUDE_DIRS})

add_library(gui STATIC ${GUI_SOURCES} ${GUI_HEADERS})
target_link_libraries(gui ${SDL2_LIBRARIES})

#C11
set_property(TARGET gui PROPERTY C_STANDARD 11)