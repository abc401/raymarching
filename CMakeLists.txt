cmake_minimum_required(VERSION 3.5)
project(raymarching VERSION 0.1.0 LANGUAGES C)

include(CTest)
enable_testing()

add_executable(raymarching src/main.c src/vec.c src/sdf.c)
target_link_libraries(raymarching PUBLIC mingw32 SDL2main SDL2)

set(CMAKE_C_STANDARD 99)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
