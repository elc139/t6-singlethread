#include <iostream>
#include "MandelbrotGenerator.h"
#include <mpi.h>

long Parse(const char* c)
{
    return strtol(c, nullptr, 10);
}

int main(int argc, char** argv)
{
    MPI_Init(nullptr, nullptr);
    int myRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

    if (argc == 3)
    {
//        MandelbrotGenerator::Generate(Parse(argv[2]), Parse(argv[1]));
    }
    else
    {
        std::cout << "DEBUG Mode"  << std::endl;
//        MandelbrotGenerator::Generate(20, 1024);
    }

    MPI_Finalize();

    return 0;
}