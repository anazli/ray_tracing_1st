#include<iostream>
#include<fstream>
#include "../include/camera.h"
#include "../include/ray.h"
#include "../include/sphere.h"
#include "../include/hitable.h"
#include "../include/hitable_list.h"

using namespace std;

Vec3 color(const Ray& r, Hitable *world)
{
    hit_record rec;
    if(world->hit(r, 0.001, MAXFLOAT, rec))
    {
        Vec3 target = rec.p + rec.normal + randomVectorOnUnitSphere();
        return 0.5 * color( Ray(rec.p, target - rec.p), world);
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


    Hitable *list[2];
    list[0] = new Sphere(Vec3(0.,0.,-1), 0.5);
    list[1] = new Sphere(Vec3(0., -100.5, -1.), 100);
    Hitable *world = new Hitable_list(list, 2);
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
                col = col + color(r, world);
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