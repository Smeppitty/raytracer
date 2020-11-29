#include <stdio.h>
#include <stdlib.h>

#include "obj.h"
#include "rt.h"
#include "vec.h"
#include "sphere.h"
#include "light.h"

//reads file based on user input in command line and populates a linked list
void read_objs(OBJ_T **list) {
    double radius;
    VEC_T center;
    COLOR_T color;

    OBJ_T *node;
    *list = NULL;
    //populates linked list
    while (scanf("%lf %lf %lf %lf %lf %lf %lf", &center.x, &center.y, &center.z, &radius, &color.R, &color.G, &color.B) == 7) {
        node = (struct OBJ *) malloc(sizeof(struct OBJ));

        node->sphere.center.x = center.x;
        node->sphere.center.y = center.y;
        node->sphere.center.z = center.z;
        node->sphere.radius = radius;
        node->color.R = color.R;
        node->color.G = color.G;
        node->color.B = color.B;

        node->next = *list;
        *list = node;
    }
}

//if sphere is hit by ray, the color changes in relation to ray
COLOR_T trace(RAY_T ray, OBJ_T *list, LIGHT_T light) {

    COLOR_T color;
    double min_t = 1000;
    double t;
    VEC_T int_pt;
    VEC_T normal;
    OBJ_T *closest_obj=NULL;
    VEC_T closest_int_pt;
    VEC_T closest_normal;

    color.R = 0.0;
    color.G = 0.0;
    color.B = 0.0;

    OBJ_T *obj;
    for (obj = list; obj != NULL; obj = obj->next) {
        if (intersect_sphere(ray, obj->sphere, &t, &int_pt, &normal)) {
            if (t < min_t) {
                closest_obj = obj;
                closest_int_pt = int_pt;
                closest_normal = normal;
                min_t = t;
            }
        }
    }
    if(closest_obj != NULL){
        color = illuminate(ray, light, list, closest_obj, closest_int_pt, closest_normal);
    }
    return color;
}
//main function
int main(void) {
    OBJ_T *list;
    OBJ_T *obj;
    RAY_T ray;
    COLOR_T color;
    LIGHT_T light;
    int width = 1000, height = 1000;

    light.loc.x = 4.0;
    light.loc.y = 10.0;
    light.loc.z = 0.0;

    read_objs(&list);

    //ppm file header
    printf("P6\n");
    printf("%d %d\n", width, height);
    printf("255\n");

    //loop across the canvas and print color values based on normalized ray direction and sphere colors to ppm file
    for (int y = 0; y < width; y++) {
        for (int x = 0; x < height; x++) {
            ray.direction.x = (-.5 + (double) x / 1000.0);
            ray.direction.y = (.5 - (double) y / 1000.0);
            ray.direction.z = 1.0;
            ray.direction = normalize(ray.direction);

            color = trace(ray, list, light);
//            printf("%f %f %f\n", color.R, color.G, color.B);

            if(color.R>1.0) {
                color.R = 1.0;
            }
            if(color.G>1.0) {
                color.G = 1.0;
            }
            if(color.B>1.0) {
                color.B = 1.0;
            }
            if(color.R<0.0) {
                color.R = 0.0;
            }
            if(color.G<0.0) {
                color.G = 0.0;
            }
            if(color.B<0.0) {
                color.B = 0.0;
            }

            printf("%c%c%c", ((unsigned char) (color.R * 255)), ((unsigned char) (color.G * 255)),
                   ((unsigned char) (color.B * 255)));
        }

        }
    for(obj=list; obj!=NULL; obj=obj->next){
        free(obj);
    }


}