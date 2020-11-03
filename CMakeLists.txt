cmake_minimum_required(VERSION 3.17)
project(philosophers3 C)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")
set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(philosophers3
        philo_three/philo_three.c
        philo_three/philo_three.h philo_three/parce_three.c philo_three/string_out_three.c philo_three/init_three.c)