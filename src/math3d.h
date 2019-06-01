#ifndef MATH3D_H
#define MATH3D_H

#include <math.h>
#include <string.h>

void
matrix_load(float a[16], float b[16]);
void
matrix_identity(float m[16]);
void
matrix_multiply(float a[16], float b[16]);
void
matrix_translate(float m[16], float x, float y, float z);
void
matrix_rotate(float* matrix, float l, float m, float n, float theta);
void
make_projection_matrix(float pmat[16], float w, float h, float fov);

#endif /* MATH3D_H */
