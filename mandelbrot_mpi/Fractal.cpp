/*
Fractal code for CS 4380 / CS 5351

Copyright (c) 2018, Texas State University. All rights reserved.

Redistribution and usage in source and binary form, with or without
modification, is only permitted for educational use.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

Author: Martin Burtscher
*/

#include "Fractal.h"

static const double Delta = 0.001;
static const double xMid = 0.23701;
static const double yMid = 0.521;

void Run(int frames, int width)
{
    // allocate picture array
    auto *pic = new unsigned char[frames * width * width];

    // compute frames
    double delta = Delta;
    for (int frame = 0; frame < frames; frame++)
    {
        const double xMin = xMid - delta;
        const double yMin = yMid - delta;
        const double dw = 2.0 * delta / width;
        for (int row = 0; row < width; row++)
        {
            const double cy = yMin + row * dw;
            for (int col = 0; col < width; col++)
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
                pic[frame * width * width + row * width + col] = (unsigned char) depth;
            }
        }
        delta *= 0.98;
    }

    // verify result by writing frames to BMP files
    for (int frame = 0; frame < frames; frame++)
    {
        char name[32];
        sprintf(name, "fractal%d.bmp", frame + 1000);
        writeBMP(width, width, &pic[frame * width * width], name);
    }

    delete[] pic;
}
