#include <math3d.h>

void
matrix_load(float a[16], float b[16])
	{
	memcpy(a, b, sizeof(float)*16);
	}
void
matrix_identity(float m[16])
	{
	memset(m, 0, 16*sizeof(float));
	m[ 0]=1; 
	m[ 5]=1; 
	m[10]=1; 
	m[15]=1; 
	}

/*
0	4	8	12
1	5	9	13
2	6	10	14
3	7	11	15
*/

void
matrix_multiply(float a[16], float b[16])
	{
	float tm[16];
	tm[ 0] = a[0]*b[ 0] + a[4]*b[ 1] + a[ 8]*b[ 2] + a[12]*b[3];
	tm[ 4] = a[0]*b[ 4] + a[4]*b[ 5] + a[ 8]*b[ 6] + a[12]*b[7];
	tm[ 8] = a[0]*b[ 8] + a[4]*b[ 9] + a[ 8]*b[10] + a[12]*b[11];
	tm[12] = a[0]*b[12] + a[4]*b[13] + a[ 8]*b[14] + a[12]*b[15];

	tm[ 1] = a[1]*b[ 0] + a[5]*b[ 1] + a[ 9]*b[ 2] + a[13]*b[3];
	tm[ 5] = a[1]*b[ 4] + a[5]*b[ 5] + a[ 9]*b[ 6] + a[13]*b[7];
	tm[ 9] = a[1]*b[ 8] + a[5]*b[ 9] + a[ 9]*b[10] + a[13]*b[11];
	tm[13] = a[1]*b[12] + a[5]*b[13] + a[ 9]*b[14] + a[13]*b[15];

	tm[ 2] = a[2]*b[ 0] + a[6]*b[ 1] + a[10]*b[ 2] + a[14]*b[3];
	tm[ 6] = a[2]*b[ 4] + a[6]*b[ 5] + a[10]*b[ 6] + a[14]*b[7];
	tm[10] = a[2]*b[ 8] + a[6]*b[ 9] + a[10]*b[10] + a[14]*b[11];
	tm[14] = a[2]*b[12] + a[6]*b[13] + a[10]*b[14] + a[14]*b[15];

	tm[ 3] = a[3]*b[ 0] + a[7]*b[ 1] + a[11]*b[ 2] + a[15]*b[3];
	tm[ 7] = a[3]*b[ 4] + a[7]*b[ 5] + a[11]*b[ 6] + a[15]*b[7];
	tm[11] = a[3]*b[ 8] + a[7]*b[ 9] + a[11]*b[10] + a[15]*b[11];
	tm[15] = a[3]*b[12] + a[7]*b[13] + a[11]*b[14] + a[15]*b[15];
	memcpy(a, tm, 16*sizeof(float));
	}

void
matrix_translate(float m[16], float x, float y, float z)
	{

	float trans[16]= {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		x,y,z,1,
		};
	matrix_multiply(m, trans);
	}
void
matrix_rotate(float* matrix, float l, float m, float n, float theta)
	{
	float rotate[16];

	rotate[0] = ((l * l) *(1-cos(theta))) + cos(theta);
	rotate[1] = ((l * m) *(1-cos(theta))) + (n*sin(theta));
	rotate[2] = ((l * n) *(1-cos(theta))) - (m*sin(theta));
	rotate[3] = 0;

	rotate[4] = ((m * l) * (1-cos(theta))) - (n * sin(theta));
	rotate[5] = ((m * m) * (1-cos(theta))) + (cos(theta));
	rotate[6] = ((m * n) * (1-cos(theta))) + (l * sin(theta));
	rotate[7] = 0;

	rotate[8] = ((n * l) * (1-cos(theta))) + (m * sin(theta));
	rotate[9] = ((n * m) * (1-cos(theta))) - (l * sin(theta));
	rotate[10] =((n * n) * (1-cos(theta))) + cos(theta);
	rotate[11] = 0;

	rotate[12]=0;
	rotate[13]=0;
	rotate[14]=0;
	rotate[15]=1;

	matrix_multiply(matrix, rotate);
	}

void
make_projection_matrix(float pmat[16], float w, float h, float fov)
	{
	float aspect = w/h;
	float n = 1;
	float f = 10000;
	float r = aspect;
	float l = -aspect;
	float t = 1;
	float b = -1;
	float height = t-b;
	n = (height / 2.0f) / tan( ((fov/180.0)*M_PI) / 2.0);
	float projection_matrix[] = {
			n/r, 0, 0, 0,
			0, n/t, 0, 0,
			0, 0, (n+f)/(n-f), -1,
			0, 0, (-2*f*n)/(f-n), 0
			};	
	memcpy(pmat, projection_matrix, sizeof(float)*16);
	}

