#pragma once

#include "Parameters.h" // Include or declare XDIM, YDIM, ZDIM

float Norm(const float (&x)[XDIM][YDIM][ZDIM]);

float InnerProduct(const float (&x)[XDIM][YDIM][ZDIM], const float (&y)[XDIM][YDIM][ZDIM]);

struct NormInnerProductResult
{
    float norm;
    float innerProduct;
};

NormInnerProductResult NormInnerProduct(const float (&x)[XDIM][YDIM][ZDIM], const float (&y)[XDIM][YDIM][ZDIM]);
