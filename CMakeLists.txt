cmake_minimum_required(VERSION 3.0.0)
project(LabySimulateur VERSION 0.1.0)

include(CTest)
enable_testing()

add_subdirectory(gui)
add_subdirectory(algorithm)

add_executable(LabySimulateur main.c)

#C11
set_property(TARGET LabySimulateur PROPERTY C_STANDARD 11)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
