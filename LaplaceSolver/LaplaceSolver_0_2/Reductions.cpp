#include "Reductions.h"

#include <algorithm>

float Norm(const float (&x)[XDIM][YDIM][ZDIM])
{
    float result = 0.;

#pragma omp parallel for reduction(max : result)
    for (int i = 1; i < XDIM - 1; i++)
        for (int j = 1; j < YDIM - 1; j++)
            for (int k = 1; k < ZDIM - 1; k++)
                result = std::max(result, std::abs(x[i][j][k]));

    return result;
}

float InnerProduct(const float (&x)[XDIM][YDIM][ZDIM], const float (&y)[XDIM][YDIM][ZDIM])
{
    double result = 0.;

#pragma omp parallel for reduction(+ : result)
    for (int i = 1; i < XDIM - 1; i++)
        for (int j = 1; j < YDIM - 1; j++)
            for (int k = 1; k < ZDIM - 1; k++)
                result += (double)x[i][j][k] * (double)y[i][j][k];

    return (float)result;
}
float CombinedCopyAndInnerProduct(const float (&x)[XDIM][YDIM][ZDIM], float (&y)[XDIM][YDIM][ZDIM])
{
    double innerProductResult = 0.0;

#pragma omp parallel for reduction(+ : innerProductResult)
    for (int i = 1; i < XDIM - 1; i++)
    {
        for (int j = 1; j < YDIM - 1; j++)
        {
            for (int k = 1; k < ZDIM - 1; k++)
            {
                y[i][j][k] = x[i][j][k];                                       // Perform the copy operation
                innerProductResult += (double)x[i][j][k] * (double)x[i][j][k]; // Calculate the inner product with itself, equivalent to a norm squared if x and y are initially the same
            }
        }
    }

    return (float)innerProductResult;
}
void Two_Saxpy(float (&p)[XDIM][YDIM][ZDIM], const float (&z)[XDIM][YDIM][ZDIM],
               float (&x)[XDIM][YDIM][ZDIM],
               const float alpha, const float beta)
{
#pragma omp parallel for
    for (int i = 1; i < XDIM - 1; i++)
        for (int j = 1; j < YDIM - 1; j++)
            for (int k = 1; k < ZDIM - 1; k++)
            {
                // combining x = x + alpha*p, p = z + beta*p to one kernal
                x[i][j][k] = x[i][j][k] + alpha * p[i][j][k];
                p[i][j][k] = z[i][j][k] + beta * p[i][j][k];
            }
}