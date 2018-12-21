#include<iostream>
#include<fstream>
#include "../include/camera.h"
#include "../include/ray.h"
#include "../include/material.h"
#include "../include/sphere.h"
#include "../include/hitable.h"
#include "../include/hitable_list.h"

using namespace std;

Vec3 color(const Ray& r, Hitable *world, int depth)
{
    hit_record rec;
    if(world->hit(r, 0.001, MAXFLOAT, rec))
    {
        Ray scattered;
        Vec3 attenuation;
        if(depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        {
            return attenuation * color(scattered, world, depth+1);
        }
        else
        {
            return Vec3(0.,0.,0.);
        }
    }
    Vec3 unit_direction = getUnitVectorOf(r.direction());
    double t = 0.5 * (unit_direction.y() + 1.);
    return (1. - t) * Vec3(1., 1., 1.) + t * Vec3(0.5, 0.7, 1.);
}

int main()
{
    int nx = 800;
    int ny = 600;
    int ns = 100;
    ofstream out;
    out.open("image.ppm");


    int Nobj = 4;
    Hitable *list[Nobj];
    list[0] = new Sphere(Vec3(0.,0.,-1), 0.5, new Lambertian(Vec3(0.8, 0.3, 0.3)));
    list[1] = new Sphere(Vec3(0., -100.5, -1.), 100, new Lambertian(Vec3(0.8,0.8,0.)));
    list[2] = new Sphere(Vec3(1., 0., -1.), 0.5, new Metal(Vec3(0.8,0.6,0.2), 0.0));
    list[3] = new Sphere(Vec3(-1., 0., -1.), 0.5, new Metal(Vec3(0.8,0.8,0.8), 0.0));
    Hitable *world = new Hitable_list(list, Nobj);
    Camera cam;

    out << "P3\n" << nx << " " << ny << "\n255\n";
    for(int j = ny ; j >= 0 ; --j)
    {
        for(int i = 0 ; i < nx ; ++i)
        {
            Vec3 col(0.,0.,0.);
            for(int s = 0 ; s < ns ; ++s)
            {
                double u = double(i + drand48())/double(nx);
                double v = double(j + drand48())/double(ny);

                Ray r = cam.get_ray(u,v);
                col = col + color(r, world, 0);
            }
            col = col/ double(ns);
            col = Vec3(sqrt(col.x()), sqrt(col.y()), sqrt(col.z()));
            int ir = int(255.99*col.x());
            int ig = int(255.99*col.y());
            int ib = int(255.99*col.z());

            out << ir << " " << ig << " " << ib << endl;
        }
    }

    out.close();

    return 0;
}