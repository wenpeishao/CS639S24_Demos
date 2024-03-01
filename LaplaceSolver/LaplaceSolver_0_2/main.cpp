#include "ConjugateGradients.h"
#include "Timer.h"
#include "Utilities.h"
#include <iostream>

extern double totalTimeComputeLaplacian;
extern double totalTimeSaxpy;
extern double totalTimeCopy;
extern double totalTimeNorm;
extern double totalTimeInnerProduct;

int main(int argc, char *argv[])
{
    using array_t = float(&)[XDIM][YDIM][ZDIM];

    float *xRaw = new float[XDIM * YDIM * ZDIM];
    float *fRaw = new float[XDIM * YDIM * ZDIM];
    float *pRaw = new float[XDIM * YDIM * ZDIM];
    float *rRaw = new float[XDIM * YDIM * ZDIM];
    float *zRaw = new float[XDIM * YDIM * ZDIM];

    array_t x = reinterpret_cast<array_t>(*xRaw);
    array_t f = reinterpret_cast<array_t>(*fRaw);
    array_t p = reinterpret_cast<array_t>(*pRaw);
    array_t r = reinterpret_cast<array_t>(*rRaw);
    array_t z = reinterpret_cast<array_t>(*zRaw);

    // Initialization
    {
        Timer timer;
        timer.Start();
        InitializeProblem(x, f);
        timer.Stop("Initialization : ");
    }

    // Call Conjugate Gradients algorithm
    ConjugateGradients(x, f, p, r, z);

    // Report the cumulative times
    std::cout << "Total time spent in ComputeLaplacian: " << totalTimeComputeLaplacian << " ms\n";
    std::cout << "Total time spent in Saxpy: " << totalTimeSaxpy << " ms\n";
    std::cout << "Total time spent in Copy: " << totalTimeCopy << " ms\n";
    std::cout << "Total time spent in Norm: " << totalTimeNorm << " ms\n";
    std::cout << "Total time spent in InnerProduct: " << totalTimeInnerProduct << " ms\n";

    // Cleanup
    delete[] xRaw;
    delete[] fRaw;
    delete[] pRaw;
    delete[] rRaw;
    delete[] zRaw;

    return 0;
}
