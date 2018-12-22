#include<iostream>
#include<fstream>
#include "../include/camera.h"
#include "../include/ray.h"
#include "../include/material.h"
#include "../include/sphere.h"
#include "../include/hitable.h"
#include "../include/hitable_list.h"

using namespace std;


Hitable *random_scene();

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
    int ns = 10;
    ofstream out;
    out.open("image.ppm");


    /*int Nobj = 5;
    Hitable *list[Nobj];
    list[0] = new Sphere(Vec3(0.,0.,-1), 0.5, new Lambertian(Vec3(0.8, 0.3, 0.3)));
    list[1] = new Sphere(Vec3(0., -100.5, -1.), 100, new Lambertian(Vec3(0.8,0.8,0.)));
    list[2] = new Sphere(Vec3(1., 0., -1.), 0.5, new Metal(Vec3(0.8,0.6,0.2), 0.0));
    list[3] = new Sphere(Vec3(-1., 0., -1.), 0.5, new Dielectric(1.5));
    list[4] = new Sphere(Vec3(-1., 0., -1.), -0.45, new Dielectric(1.5));

    Hitable *world = new Hitable_list(list, Nobj);*/

    Hitable *world = random_scene();

    Vec3 lookfrom(13., 2., 3.);
    Vec3 lookat(0., 0., 0);
    double dist_to_focus = 10.;
    double aperture = 0.1;

    Camera cam(lookfrom, lookat, Vec3(0., 1., 0.), 20., double(nx)/double(ny),
                                                     aperture, dist_to_focus);

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

Hitable *random_scene()
{
    int n = 500;
    Hitable **list = new Hitable*[n+1];
    list[0] = new Sphere(Vec3(0., -1000., 0.), 1000, new Lambertian(Vec3(0.5, 0.5, 0.5)));
    int i = 1;
    for(int a = -11 ; a < 11 ; a++)
    {
        for(int b = -11 ; b < 11 ; b++)
        {
            double choose_mat = drand48();
            Vec3 center(a + 0.9*drand48(), 0.2, b + 0.9*drand48());
            if((center - Vec3(4., 0.2, 0.)).magnitude() > 0.9)
            {
                if(choose_mat < 0.8) //diffuse
                {
                    list[i++] = new Sphere(center, 0.2,
                         new Lambertian(Vec3(drand48()*drand48(),
                                     drand48()*drand48(), drand48()*drand48())));
                }
                else if(choose_mat < 0.95) //metal
                {
                    list[i++] = new Sphere(center, 0.2,
                         new Metal(Vec3(0.5 * (1. + drand48()),
                                     0.5 * (1. + drand48()), 0.5 * (1. + drand48())), 0.5*drand48()));
                    
                }
                else
                {
                    list[i++] = new Sphere(center, 0.2, new Dielectric(1.5));
                }
            }
        }
    }

    list[i++] = new Sphere(Vec3(0., 1., 0.), 1., new Dielectric(1.5));
    list[i++] = new Sphere(Vec3(-4., 1., 0.), 1., new Lambertian(Vec3(0.4, 0.2, 0.1)));
    list[i++] = new Sphere(Vec3(4., 1., 0.), 1., new Metal(Vec3(0.7, 0.6, 0.5), 0.));

    return new Hitable_list(list, i);
}