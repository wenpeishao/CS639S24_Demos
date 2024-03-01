#include "Laplacian.h"
#include "Parameters.h"
#include "PointwiseOps.h"
#include "Reductions.h"
#include "Utilities.h"
#include "Timer.h"

#include <iostream>

// Global variables for timing
double totalTimeComputeLaplacian = 0.0;
double totalTimeSaxpy = 0.0;
double totalTimeCopy = 0.0;
double totalTimeNorm = 0.0;
double totalTimeInnerProduct = 0.0;

void ConjugateGradients(
    float (&x)[XDIM][YDIM][ZDIM],
    const float (&f)[XDIM][YDIM][ZDIM],
    float (&p)[XDIM][YDIM][ZDIM],
    float (&r)[XDIM][YDIM][ZDIM],
    float (&z)[XDIM][YDIM][ZDIM],
    const bool writeIterations)
{
    Timer timer;

    // Algorithm : Line 2
    timer.Start();
    ComputeLaplacian(x, z);
    timer.Stop();
    totalTimeComputeLaplacian += timer.Elapsed();

    timer.Start();
    Saxpy(z, f, r, -1);
    timer.Stop();
    totalTimeSaxpy += timer.Elapsed();

    timer.Start();
    float nu = Norm(r);
    timer.Stop();
    totalTimeNorm += timer.Elapsed();

    // Algorithm : Line 3
    if (nu < nuMax)
        return;

    // Algorithm : Line 4
    timer.Start();
    Copy(r, p);
    timer.Stop();
    totalTimeCopy += timer.Elapsed();

    timer.Start();
    float rho = InnerProduct(p, r);
    timer.Stop();
    totalTimeInnerProduct += timer.Elapsed();

    // Beginning of loop from Line 5
    for (int k = 0;; k++)
    {
        std::cout << "Residual norm (nu) after " << k << " iterations = " << nu << std::endl;

        timer.Start();
        ComputeLaplacian(p, z);
        timer.Stop();
        totalTimeComputeLaplacian += timer.Elapsed();

        timer.Start();
        float sigma = InnerProduct(p, z);
        timer.Stop();
        totalTimeInnerProduct += timer.Elapsed();

        float alpha = rho / sigma;

        timer.Start();
        Saxpy(z, r, r, -alpha);
        timer.Stop();
        totalTimeSaxpy += timer.Elapsed();

        timer.Start();
        nu = Norm(r);
        timer.Stop();
        totalTimeNorm += timer.Elapsed();

        if (nu < nuMax || k == kMax)
        {
            timer.Start();
            Saxpy(p, x, x, alpha);
            timer.Stop();
            totalTimeSaxpy += timer.Elapsed();
            std::cout << "Conjugate Gradients terminated after " << k << " iterations; residual norm (nu) = " << nu << std::endl;
            if (writeIterations)
                WriteAsImage("x", x, k, 0, 127);
            return;
        }

        timer.Start();
        Copy(r, z);
        timer.Stop();
        totalTimeCopy += timer.Elapsed();

        timer.Start();
        float rho_new = InnerProduct(z, r);
        timer.Stop();
        totalTimeInnerProduct += timer.Elapsed();

        float beta = rho_new / rho;
        rho = rho_new;

        timer.Start();
        Saxpy(p, x, x, alpha);
        timer.Stop();
        totalTimeSaxpy += timer.Elapsed();

        timer.Start();
        Saxpy(p, r, p, beta);
        timer.Stop();
        totalTimeSaxpy += timer.Elapsed();

        if (writeIterations)
            WriteAsImage("x", x, k, 0, 127);
    }
}
