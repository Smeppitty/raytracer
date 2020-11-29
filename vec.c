#include <math.h>
#include "vec.h"
//normalizes a VECTOR v
VEC_T normalize(VEC_T v){
	double mag;

	mag = sqrt((v.x*v.x) + (v.y*v.y)+ (v.z*v.z));
	if (mag == 0) {
		v.x = v.y = v.z = 0;
	}
	else {
		v.x /= mag;
		v.y /= mag;
		v.z /= mag;
	}
	return v;
}

double dot(VEC_T v1, VEC_T v2){
    double dotp;
    dotp = ((v1.x*v2.x)+(v1.y*v2.y)+(v1.z*v2.z));
      return dotp;
}
