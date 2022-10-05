cmake_minimum_required(VERSION 3.0.0)
project(LabySimulateur VERSION 0.1.0)

include(CTest)
enable_testing()

#we are in simulator
add_definitions(-DSIMULATOR)

add_subdirectory(gui)
add_subdirectory(algorithm)

file(GLOB MAIN_HEADERS ./*.h)
file(GLOB MAIN_SOURCES ./*.c)

add_executable(LabySimulateur ${MAIN_HEADERS} ${MAIN_SOURCES})
target_link_libraries(LabySimulateur gui algorithm m)

#C11
set_property(TARGET LabySimulateur PROPERTY C_STANDARD 11)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
