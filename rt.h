#ifndef RT_H
#define RT_H
#include "vec.h"

typedef struct{
    VEC_T origin;
    VEC_T direction;
}RAY_T;

typedef struct{
    double R,G,B;
}COLOR_T;

#endif