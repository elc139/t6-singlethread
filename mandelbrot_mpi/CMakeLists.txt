cmake_minimum_required(VERSION 3.19)
project(mandelbrot)

find_package(MPI REQUIRED)
add_executable(mandelbrot Fractal.cpp Fractal.h main.cpp MandelbrotGenerator.h MandelbrotManager.h MandelbrotWorker.h PacketTag.h)
target_link_libraries(mandelbrot PUBLIC MPI::MPI_CXX)
