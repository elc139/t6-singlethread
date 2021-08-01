#include "MandelbrotGenerator.h"
#include <mpi.h>
#include "MandelbrotManager.h"
#include "MandelbrotWorker.h"


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
        MandelbrotManager::Start(argc, argv);
    }
    else
    {
        MandelbrotWorker::Start();
    }

    MPI_Finalize();

    return 0;
}