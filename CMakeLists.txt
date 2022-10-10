cmake_minimum_required(VERSION 3.0.0)
project(LabySimulateur VERSION 0.1.0)

include(CTest)
enable_testing()

#we are in simulator
add_definitions(-DSIMULATOR)

add_subdirectory(simulator)
add_subdirectory(algorithm)

file(GLOB MAIN_HEADERS ./*.h)
file(GLOB MAIN_SOURCES ./*.c)
file(GLOB LABY_HEADERS ./laby/*.h)
file(GLOB LABY_SOURCES ./laby/*.c)


add_executable(LabySimulateur ${MAIN_HEADERS} ${MAIN_SOURCES} ${LABY_SOURCES} ${LABY_HEADERS})
target_link_libraries(LabySimulateur simulator algorithm m)

#C11
set_property(TARGET LabySimulateur PROPERTY C_STANDARD 11)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
