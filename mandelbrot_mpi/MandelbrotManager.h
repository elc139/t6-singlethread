//
// Created by lorenzo on 31/07/2021.
//

#ifndef MANDELBROT_MANDELBROT_MANAGER_H
#define MANDELBROT_MANDELBROT_MANAGER_H
#include <sstream>
#include <iostream>
#include <chrono>
#include "PacketTag.h"

class MandelbrotManager
{

static long Parse(const char* c)
{
    return strtol(c, nullptr, 10);
}

public:
    static void Start(int argc, char **argv)
    {
        std::cout << argc << std::endl;

        const float delta = 0.001f;
        const float deltaAcceleration = 0.98f;

        auto startTime = std::chrono::system_clock::now();

        int resolution = (argc == 3) ? (int) Parse(argv[1]) : 512;
        int frames = (argc == 3) ? (int) Parse(argv[2]) : 50;
        int workers;
        MPI_Comm_size(MPI_COMM_WORLD, &workers);
        workers--; // Since the manager won't be a worker

        // Static schedule
        // Split work into assignees and dispatch to each worker async
        for (int i = 0; i < workers; i++)
        {
            int rank = i + 1; // Rank zero is reserved for manager

            int start = i * frames / workers;
            int end = i == workers - 1 ? frames - 1 : (i + 1) * frames / workers - 1;

            int data[3] = {start, end - start, resolution};
            std::stringstream msg;
            msg << "Dispatching request to worker " << rank << " to process from " << start << " to " << end << std::endl;
            std::cout << msg.str(); // Avoids race condition
            MPI_Send(data, 3, MPI_INT, rank, PacketTag::Request, MPI_COMM_WORLD);
        }

        int frameIndex = 0;
        for (int i = 0; i < workers; i++)
        {
            int rank = i + 1; // Rank zero is reserved for manager

            int start = i * frames / workers;
            int end = i == workers - 1 ? frames - 1 : (i + 1) * frames / workers - 1;

            int workerFrames = end - start;
            int frameSize = resolution * resolution;
            int bufferSize = workerFrames * frameSize;
            std::vector<uchar> batch(bufferSize);
            MPI_Recv(batch.data(), bufferSize, MPI_UNSIGNED_CHAR, rank, PacketTag::Reply, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            //for (int frame = 0; frame < workerFrames; frame++)
            //{
                // char name[32];
                //sprintf(name, "Mandelbrot%d.bmp", frameIndex+++ 1000);
                //writeBMP(resolution, resolution, &batch[frame * resolution * resolution], name);
            //}
        }

        auto end = std::chrono::system_clock::now();

        std::chrono::duration<double> elapsed_seconds = end - startTime;

        std::cout << "Elapsed time: " << elapsed_seconds.count() << "s\n";

    }
};


#endif //MANDELBROT_MANDELBROT_MANAGER_H
