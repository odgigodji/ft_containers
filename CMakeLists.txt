cmake_minimum_required(VERSION 3.19)
project(ft_containers)

set(CMAKE_CXX_STANDARD 14)

SET(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wextra -Werror")
SET(GCC_COVERAGE_LINK_FLAGS    "-Wall -Wextra -Werror")
include_directories(.)

add_executable(ft_containers
        main.cpp
        vector.hpp
        iterators.hpp
        ft.hpp stack.hpp
        stack.hpp
        ft_containers-unit-test/config.hpp
        map.hpp
        )
