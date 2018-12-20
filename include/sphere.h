#ifndef SPHERE_H
#define SPHERE_H

#include "hitable.h"

class Sphere : public Hitable {

    public:

        Sphere(){}
        Sphere(Vec3 cen, double r) : center(cen), radius(r) {}
        
        virtual bool hit(const Ray& r, double t_min, double t_max,
                                                     hit_record& rec) const;

        Vec3 center;
        double radius;
};


bool Sphere::hit(const Ray& r, double t_min, double t_max,
                                             hit_record& rec)const
{
    Vec3 oc = r.origin() - center;
    double a = dot(r.direction(), r.direction());
    double b = dot(oc, r.direction());
    double c = dot(oc, oc) - radius*radius;
    double discriminant = b*b - a*c;
    if(discriminant > 0)
    {
        double temp = (-b - sqrt(discriminant))/a;
        if(temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center)/radius;
            return true;
        }
        temp = (-b + sqrt(discriminant))/a;
        if(temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center)/radius;
            return true;
        }
    }
    return false;
}

#endif