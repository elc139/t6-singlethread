cmake_minimum_required(VERSION 3.19)
project(mandelbrot_mpi)

set(CMAKE_CXX_STANDARD 14)

add_executable(mandelbrot_mpi Fractal.cpp Fractal.h main.cpp MandelbrotGenerator.h)