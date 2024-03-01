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
struct NormInnerProductResult
{
    float norm;
    float innerProduct;
};

NormInnerProductResult NormInnerProduct(const float (&x)[XDIM][YDIM][ZDIM], const float (&y)[XDIM][YDIM][ZDIM])
{
    float maxNorm = 0.;
    double sumInnerProduct = 0.;

#pragma omp parallel for reduction(max : maxNorm) reduction(+ : sumInnerProduct)
    for (int i = 1; i < XDIM - 1; i++)
    {
        for (int j = 1; j < YDIM - 1; j++)
        {
            for (int k = 1; k < ZDIM - 1; k++)
            {
                maxNorm = std::max(maxNorm, std::abs(x[i][j][k]));
                sumInnerProduct += (double)x[i][j][k] * (double)y[i][j][k];
            }
        }
    }

    return {maxNorm, (float)sumInnerProduct};
}
