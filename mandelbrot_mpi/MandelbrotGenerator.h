//
// Created by Lorenzo on 7/29/12021.
//

#ifndef MANDELBROT_MPI_MANDELBROT_GENERATOR_H
#define MANDELBROT_MPI_MANDELBROT_GENERATOR_H

#include "Fractal.h"
#include <vector>
static const double xMid = 0.23701;
static const double yMid = 0.521;

typedef unsigned char uchar;

class MandelbrotGenerator
{
public:
    static void Generate(std::vector<uchar>& pic, float delta, float deltaAcceleration, int frames, int dimension)
    {
        for (int frame = 0; frame < frames; frame++)
        {
            const double xMin = xMid - delta;
            const double yMin = yMid - delta;
            const double dw = 2.0 * delta / dimension;
            for (int row = 0; row < dimension; row++)
            {
                const double cy = yMin + row * dw;
                for (int col = 0; col < dimension; col++)
                {
                    const double cx = xMin + col * dw;
                    double x = cx;
                    double y = cy;
                    int depth = 256;
                    double x2, y2;
                    do
                    {
                        x2 = x * x;
                        y2 = y * y;
                        y = 2 * x * y + cy;
                        x = x2 - y2 + cx;
                        depth--;
                    } while ((depth > 0) && ((x2 + y2) < 5.0));
                    pic[frame * dimension * dimension + row * dimension + col] = (unsigned char) depth;
                }
            }
            delta *= deltaAcceleration;
        }

    }
};


#endif //MANDELBROT_MPI_MANDELBROT_GENERATOR_H
