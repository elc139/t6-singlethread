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

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;

    MPI_Get_processor_name(processor_name, &name_len);

    if (myRank == 0)
    {
        printf("Master process running in %s, rank %d out of %d processors\n", processor_name, myRank, size);
    }
    else
    {
        printf("Slave process running in %s, rank %d out of %d processors\n", processor_name, myRank, size);
    }

    if (argc == 3)
    {
//        MandelbrotGenerator::Generate(Parse(argv[2]), Parse(argv[1]));
    }
    else
    {
        std::cout << "DEBUG Mode"  << std::endl;
        //MandelbrotGenerator::Generate(20, 1024);
    }

    MPI_Finalize();

    return 0;
}