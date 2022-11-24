cmake_minimum_required(VERSION 3.24)
project(game_of_life C)

set(CMAKE_C_STANDARD 90)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR} "include/")

add_compile_options(-Wall -Wextra -Wconversion -Werror -pedantic -O0 -g3 -fsanitize=address,undefined)
add_link_options(-fsanitize=address,undefined)
add_executable(game_of_life src/main.c src/gol.c include/gol.h)
target_link_libraries(game_of_life ${CURSES_LIBRARIES})
