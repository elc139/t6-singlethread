//
// Created by lorenzo on 31/07/2021.
//

#ifndef MANDELBROT_MANDELBROT_WORKER_H
#define MANDELBROT_MANDELBROT_WORKER_H

#include <sstream>
#include <iostream>
#include <sstream>
#include "PacketTag.h"

class MandelbrotWorker
{
public:

    static void Start()
    {
        int data[3];
        MPI_Recv(&data, 3, MPI_INT, 0, PacketTag::Request, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        int start = data[0];
        int frames = data[1];
        int resolution = data[2];
        std::stringstream msg;
        msg << "Received work from frame " << start << " to " << start + frames << " with resolution " << resolution << std::endl;
        std::cout << msg.str(); // Avoids race condition
        std::vector<uchar> batch(frames * resolution * resolution);
        float delta = 0.001f;
        float deltaAcceleration = 0.98f;
        for (int i = 0; i < start; i++)
        {
            delta *= deltaAcceleration;
        }
        MandelbrotGenerator::Generate(batch, delta, deltaAcceleration, frames, resolution);
        MPI_Send(batch.data(), (int) batch.size(), MPI_UNSIGNED_CHAR, 0, PacketTag::Reply, MPI_COMM_WORLD);
    }
};


#endif //MANDELBROT_MANDELBROT_WORKER_H
