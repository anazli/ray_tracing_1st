#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"

class Camera {

    public:

        Camera() {
            lower_left_corner = Vec3(-2., -1., -1.);
            horizontal = Vec3(4., 0., 0.);
            vertical = Vec3(0., 2., 0.);
            origin = Vec3(0., 0., 0.);
        }

        Ray get_ray(double u, double v)
        {return Ray(origin, lower_left_corner + u*horizontal +
                                         v*vertical - origin);}

        Vec3 origin;
        Vec3 lower_left_corner;
        Vec3 horizontal;
        Vec3 vertical;
};

#endif