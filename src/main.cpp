#include<iostream>
#include<fstream>
#include "../include/ray.h"
#include "../include/sphere.h"
#include "../include/hitable.h"
#include "../include/hitable_list.h"

using namespace std;

Vec3 color(const Ray& r, Hitable *world)
{
    hit_record rec;
    if(world->hit(r, 0., MAXFLOAT, rec))
    {
        return 0.5 * Vec3(rec.normal.x()+1, rec.normal.y()+1, rec.normal.z()+1);
    }
    Vec3 unit_direction = getUnitVectorOf(r.direction());
    double t = 0.5 * (unit_direction.y() + 1.);
    return (1. - t) * Vec3(1., 1., 1.) + t * Vec3(0.5, 0.7, 1.);
}

int main()
{
    int nx = 800;
    int ny = 600;
    ofstream out;
    out.open("image.ppm");

    Vec3 lower_left_corner(-2., -1., -1.);
    Vec3 horizontal(4., 0., 0.);
    Vec3 vertical(0., 2., 0.);
    Vec3 origin(0., 0., 0.);

    Hitable *list[2];
    list[0] = new Sphere(Vec3(0.,0.,-1), 0.5);
    list[1] = new Sphere(Vec3(0., -100.5, -1.), 100);
    Hitable *world = new Hitable_list(list, 2);

    out << "P3\n" << nx << " " << ny << "\n255\n";
    for(int j = ny ; j >= 0 ; --j)
    {
        for(int i = 0 ; i < nx ; ++i)
        {

            double u = double(i)/double(nx);
            double v = double(j)/double(ny);

            Ray r(origin, lower_left_corner + u * horizontal + v * vertical);
            Vec3 col = color(r, world);

            int ir = int(255.99*col.x());
            int ig = int(255.99*col.y());
            int ib = int(255.99*col.z());

            out << ir << " " << ig << " " << ib << endl;
        }
    }

    out.close();

    return 0;
}