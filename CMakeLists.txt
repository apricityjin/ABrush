cmake_minimum_required(VERSION 3.25)
project(ABrush)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled main.cpp Point.cpp Point.h Path.cpp Path.h ABrush.h Affine.cpp Affine.h FillTessellator.cpp FillTessellator.h libtess2/Source/tess.c libtess2/Source/sweep.c libtess2/Source/priorityq.c libtess2/Source/mesh.c libtess2/Source/geom.c libtess2/Source/dict.c libtess2/Source/bucketalloc.c StrokeTessellator.cpp StrokeTessellator.h)
