cmake_minimum_required(VERSION 3.25)
project(ABrush)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled main.cpp Point.cpp Point.h Path.cpp Path.h ABrush.h Affine.cpp Affine.h)
