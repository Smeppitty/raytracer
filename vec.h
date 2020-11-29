#ifndef VEC_H
#define VEC_H
//vector has 3 coordinates
typedef struct{
	double x,y,z;
}VEC_T;
//normalize vector
VEC_T normalize(VEC_T vector);
//dot product
double dot(VEC_T v1, VEC_T v2);

#endif