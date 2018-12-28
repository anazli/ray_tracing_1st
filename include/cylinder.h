#ifndef CYLINDER_H
#define CYLINDER_H

#include "hitable.h"
#include<iostream>
#include<cmath>

class Cylinder : public Hitable {

    public:

        Cylinder(){}
        Cylinder(Vec3 cen, double h, double r, Material *m) :
         center(cen), height(h), radius(r), mat_ptr(m) {}
        
        virtual bool hit(const Ray& r, double t_min, double t_max,
                                                     hit_record& rec) const;

        Vec3 center;
        double height;
        double radius;
        Material *mat_ptr;
};


bool Cylinder::hit(const Ray& r, double t_min, double t_max,
                                             hit_record& rec)const
{
    Vec3 oc = r.origin() - center;
    Vec3 orientation(1.,0.,1.);
    double ymin = center.y();
    double ymax = ymin + height;
    double a = dot(r.direction() * orientation, r.direction());
    double b = dot(2. * oc * orientation, r.direction());
    double c = dot(oc * orientation, oc) - radius * radius;
    double discriminant = b*b - 4.*a*c;
    if(discriminant >= 0)
    {
        double temp1 = (-b - sqrt(discriminant))/a;
        if(temp1 < t_max && temp1 > t_min)
        {
            double l;
            Vec3 temp_vec = r.point_at_parameter(temp1);
            l = temp_vec.y();
            if(l == ymin)
            {
                double intersection = (ymin - r.origin().y())/r.direction().y();
                if(intersection >= 0)
                {
                    if(intersection < t_max && intersection > t_min)
                    {
                        rec.t = temp1;
                        rec.p = r.point_at_parameter(rec.t);
                        rec.normal = Vec3(0.,-1.,0.);
                        rec.mat_ptr = mat_ptr;
                        return true;
                    }
                }
            }
            else if(l == ymax)
            {
                double intersection = (ymax - r.origin().y())/r.direction().y();
                if(intersection >= 0)
                {
                    rec.t = temp1;
                    rec.p = r.point_at_parameter(rec.t);
                    rec.normal = Vec3(0.,1.,0.);
                    rec.mat_ptr = mat_ptr;
                    return true;
                }
            }
            else if(l > ymin && l < ymax)
            {
                rec.t = temp1;
                rec.p = r.point_at_parameter(rec.t);
                double theta = atan(rec.p.z()/rec.p.x());
                Vec3 n(cos(theta), 0., sin(theta));
                rec.normal = n;
                rec.mat_ptr = mat_ptr;
                return true;
            }
        }
        double temp2 = (-b + sqrt(discriminant))/a;
        if(temp2 < t_max && temp2 > t_min)
        {
            double l;
            Vec3 temp_vec = r.point_at_parameter(temp2);
            l = temp_vec.y();
            if(l == ymin)
            {
                double intersection = (ymin - r.origin().y())/r.direction().y();
                if(intersection >= 0)
                {
                    rec.t = temp2;
                    rec.p = r.point_at_parameter(rec.t);
                    rec.normal = Vec3(0.,-1.,0.);
                    rec.mat_ptr = mat_ptr;
                    return true;
                }
            }
            else if(l == ymax)
            {
                double intersection = (ymax - r.origin().y())/r.direction().y();
                if(intersection >= 0)
                {
                    rec.t = temp2;
                    rec.p = r.point_at_parameter(rec.t);
                    rec.normal = Vec3(0.,1.,0.);
                    rec.mat_ptr = mat_ptr;
                    return true;
                }
            }
            else if(l > ymin && l < ymax)
            {
                rec.t = temp2;
                rec.p = r.point_at_parameter(rec.t);
                double theta = atan(rec.p.z()/rec.p.x());
                Vec3 n(cos(theta), 0., sin(theta));
                rec.normal = n;
                rec.mat_ptr = mat_ptr;
                return true;
            }
        }
    }
    return false;
}

#endif