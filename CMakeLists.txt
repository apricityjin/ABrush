cmake_minimum_required(VERSION 3.25)
project(ABrush)

set(CMAKE_CXX_STANDARD 17)

add_executable(ABrush main.cpp Point.h ABrush.h Affine.h Path.h FillTessellator.h libtess2/Source/bucketalloc.c libtess2/Source/dict.c libtess2/Source/geom.c libtess2/Source/mesh.c libtess2/Source/priorityq.c libtess2/Source/sweep.c libtess2/Source/tess.c StrokeTessellator.h Builder.h RenderData.h Texture.h Color.h Image.h Gradient.h)
