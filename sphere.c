#include <stdio.h>
#include <math.h>
#include "rt.h"
#include "sphere.h"
#include "vec.h"

int intersect_sphere(RAY_T ray, SPHERE_T sphere, double *t, VEC_T *int_pt, VEC_T *normal){

    VEC_T difference;

    //distances between ray and sphere based on ray direction
    difference.x = (ray.origin.x - sphere.center.x) * ray.direction.x;
    difference.y = (ray.origin.y - sphere.center.y) * ray.direction.y;
    difference.z = (ray.origin.z - sphere.center.z) * ray.direction.z;

    double totalDifference = difference.x + difference.y + difference.z;  //curtailed for b

    //quadratic formula elements (-b +- sqrt((b)^2-4ac))/2a
    double a = 1.0;
    double b = 2.0 * (totalDifference);
    double c = (ray.origin.x - sphere.center.x) * (ray.origin.x - sphere.center.x) +
               (ray.origin.y - sphere.center.y) * (ray.origin.y - sphere.center.y) +
               (ray.origin.z - sphere.center.z) * (ray.origin.z - sphere.center.z) - (sphere.radius * sphere.radius);

    double discriminant = b * b - 4 * a * c; // discriminant b^2 - 4ac
    //if discriminant is lower or equal to 0, it does not intersect it
    if (discriminant < 0) {
        return 0;
    } else { //two roots t1 and t2 are found through continuation of the quadratic formula
        discriminant = sqrt(discriminant);
        double t1 = (-b - discriminant) / (2.0*a);
        double t2 = (-b + discriminant) / (2.0*a);
        //tests which root we can see hit the sphere
        if (t1<0 && t2<0){return 0;}
        if (t1 < t2) {
            *t = t1;
        } else {
            *t = t2;
        }
        //calculates the intersection point
        int_pt->x = (ray.origin.x + ray.direction.x * *t);
        int_pt->y = (ray.origin.y + ray.direction.y * *t);
        int_pt->z = (ray.origin.z + ray.direction.z * *t);

        //calculates the normal
        normal->x =(int_pt->x-sphere.center.x)/sphere.radius;
        normal->y =(int_pt->y-sphere.center.y)/sphere.radius;
        normal->z =(int_pt->z-sphere.center.z)/sphere.radius;
        return 1;
    }
}
