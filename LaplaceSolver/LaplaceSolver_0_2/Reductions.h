#pragma once

#include "Parameters.h" // Include or declare XDIM, YDIM, ZDIM

float Norm(const float (&x)[XDIM][YDIM][ZDIM]);

float InnerProduct(const float (&x)[XDIM][YDIM][ZDIM], const float (&y)[XDIM][YDIM][ZDIM]);

float CombinedCopyAndInnerProduct(const float (&x)[XDIM][YDIM][ZDIM], float (&y)[XDIM][YDIM][ZDIM]);

void Two_Saxpy(float (&p)[XDIM][YDIM][ZDIM], const float (&z)[XDIM][YDIM][ZDIM],
               float (&x)[XDIM][YDIM][ZDIM],
               const float alpha, const float beta)
