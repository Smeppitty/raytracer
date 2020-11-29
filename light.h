#ifndef LIGHT_H
#define LIGHT_H

#include "obj.h"

typedef struct{
VEC_T loc;
}LIGHT_T;

COLOR_T illuminate (RAY_T ray, LIGHT_T light, OBJ_T *list,OBJ_T *curr_obj, VEC_T int_pt, VEC_T normal);
static int shadow_test (LIGHT_T light, OBJ_T *list, OBJ_T *curr_obj,VEC_T int_pt);
#endif