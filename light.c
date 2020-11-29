#include <stdio.h>
#include <math.h>
#include "light.h"
COLOR_T illuminate (RAY_T ray, LIGHT_T light, OBJ_T *list,OBJ_T *curr_obj, VEC_T int_pt, VEC_T normal){
    RAY_T secondary_lightray;
    VEC_T specular_direction;
    COLOR_T color;

    double dp;
    double dp2;

//ambient
    color.R = (.1*(curr_obj->color.R));
    color.G = (.1*(curr_obj->color.G));
    color.B = (.1*(curr_obj->color.B));

    if(shadow_test(light, list, curr_obj, int_pt)) {} else{
//diffuse
        secondary_lightray.origin = int_pt;

        secondary_lightray.direction.x = light.loc.x - int_pt.x;
        secondary_lightray.direction.y = light.loc.y - int_pt.y;
        secondary_lightray.direction.z = light.loc.z - int_pt.z;

        secondary_lightray.direction = normalize(secondary_lightray.direction);
        dp = dot(secondary_lightray.direction, normal);
        if(dp>0) {

            color.R += dp * (curr_obj->color.R);
            color.G += dp * (curr_obj->color.G);
            color.B += dp * (curr_obj->color.B);

            //specular
            specular_direction.x = secondary_lightray.direction.x - normal.x * 2.0 * dp;
            specular_direction.y = secondary_lightray.direction.y - normal.y * 2.0 * dp;
            specular_direction.z = secondary_lightray.direction.z - normal.z * 2.0 * dp;
            specular_direction = normalize(specular_direction);
            dp2 = dot(specular_direction,ray.direction);

            if(dp2>0) {
                color.R += (pow(dp2,200));
                color.G += (pow(dp2,200));
                color.B += (pow(dp2,200));
            }

        }

    }
    return color;
}

static int shadow_test (LIGHT_T light, OBJ_T *list, OBJ_T *curr_obj, VEC_T int_pt) {
    OBJ_T *curr;
    VEC_T normal;
    double t;
    RAY_T ray;
    //compute light Ray
    ray.origin = int_pt;

    ray.direction.x = light.loc.x - int_pt.x;
    ray.direction.y = light.loc.y - int_pt.y;
    ray.direction.z = light.loc.z - int_pt.z;

    ray.direction=normalize(ray.direction);
    for (curr = list; curr != NULL; curr = curr->next) {
        if (curr != curr_obj) { //don't self-shadow
            if (intersect_sphere(ray, curr->sphere, &t, &int_pt, &normal)) {
                return 1;  //return true
            }

        }
    }
    return 0;
}
