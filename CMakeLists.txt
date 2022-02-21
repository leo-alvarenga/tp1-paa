cmake_minimum_required(VERSION 3.21)
project(TP1_PAA C)

set(CMAKE_C_STANDARD 99)

add_executable(TP1_PAA main.c map/Map.c map/Map.h entities/Actors.c entities/Actors.h interface/Interface.c interface/Interface.h input/Input.c input/Input.h list/List.c list/List.h)
