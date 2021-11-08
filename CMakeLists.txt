cmake_minimum_required(VERSION 3.19)
project(ft_containers)

set(CMAKE_CXX_STANDARD 14)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=")

include_directories(.)

add_executable(ft_containers
#        main.cpp

        vector.hpp
        ft.hpp stack.hpp
        stack.hpp
        ft_containers-unit-test/config.hpp
        map.hpp
#        mains/ft_pair.cpp
#        mains/map_insert.cpp
        mains/AVL.cpp
        )
