#include <iostream>
#include "MandelbrotGenerator.h"

int Parse(const char* c)
{
    return strtol(c, nullptr, 10);
}

int main(int argc, char** argv)
{
    if (argc == 3)
    {
//        MandelbrotGenerator::Generate(Parse(argv[2]), Parse(argv[1]));
    }
    else if (argc == 1)
    {
        std::cout << "DEBUG Mode"  << std::endl;
//        MandelbrotGenerator::Generate(20, 1024);
    }
    else
    {
        std::cerr << "Usage: mandelbrot frame_width num_frames" << std::endl;
        return -1;
    }

    return 0;
}