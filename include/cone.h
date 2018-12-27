#ifndef CONE_H
#define CONE_H

#include "hitable.h"

class Cone : public Hitable {

    public:

        Cone(){}
        Cone(Vec3 cen, double h, double t, Material *m) : 
        center(cen), height(h), theta(t), mat_ptr(m) {}
        
        virtual bool hit(const Ray& r, double t_min, double t_max,
                                                     hit_record& rec) const;

        Vec3 center;
        double height;
        double theta;
        Material *mat_ptr;
};


bool Cone::hit(const Ray& r, double t_min, double t_max,
                                             hit_record& rec)const
{
    Vec3 oc = r.origin() - center;
    Vec3 norm(0., 1., 0.);
    double a = dot(r.direction().x(), r.direction().x())
             + dot(r.direction().z(), r.direction().z())
             - dot(r.direction().y(), r.direction().y());
    double b = 2. * dot(oc.x(), r.direction().x())
             + 2. * dot(oc.z(), r.direction().z())
             - 2. * dot(oc.y(), r.direction().y());
    double c = dot(oc.x(), oc.x())
             + dot(oc.z(), oc.z())
             - dot(oc.y(), oc.y());

    /*double a = dot(r.direction(), norm)*dot(r.direction(), norm) - cos(theta)*cos(theta);
    double b = 2. * (dot(r.direction(), norm) * dot(oc, norm) - dot(r.direction(), oc)*cos(theta)*cos(theta));
    double c = dot(oc,norm)*dot(oc,norm) - dot(oc,oc)*cos(theta)*cos(theta);
    */

    double discriminant = b*b - 4.*a*c;
    if(discriminant >= 0)
    {
        double temp = (-b - sqrt(discriminant))/a;
        if(temp < t_max && temp > t_min)
        {
            Vec3 temp_vec = r.point_at_parameter(temp);
            if(temp_vec.y() >= center.y() && temp_vec.y() <= (center.y() + height))
            {
                rec.t = temp;
                rec.p = r.point_at_parameter(rec.t);
                Vec3 v = rec.p - center;
                v.setY(0.);
                v = getUnitVectorOf(v);
                //v.setX(v.x()*(height/radius));
                //v.setZ(v.z()*(height/radius));
                rec.normal = v;
                rec.mat_ptr = mat_ptr;
                return true;
            }
        }
        temp = (-b + sqrt(discriminant))/a;
        if(temp < t_max && temp > t_min)
        {
            Vec3 temp_vec = r.point_at_parameter(temp);
            if(temp_vec.y() >= center.y() && temp_vec.y() <= (center.y() + height))
            {
                rec.t = temp;
                rec.p = r.point_at_parameter(rec.t);
                Vec3 v = rec.p - center;
                v.setY(0.);
                v = getUnitVectorOf(v);
                //v.setX(v.x()*(height/radius));
                //v.setZ(v.z()*(height/radius));
                rec.normal = v;
                rec.mat_ptr = mat_ptr;
                return true;
            }
        }
    }
    return false;
}

#endif