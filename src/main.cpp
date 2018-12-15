#include<iostream>
#include<fstream>
#include "../include/ray.h"

using namespace std;

Vec3 color(const Ray& r)
{
    Vec3 unit_direction = getUnitVectorOf(r.direction());
    double t = 0.5 * (unit_direction.y() + 1.);
    return (1. - t) * Vec3(1., 1., 1.) + t * Vec3(0.5, 0.7, 1.);
}

int main()
{
    int nx = 800;
    int ny = 600;
    ofstream out;
    out.open("picture.ppm");

    Vec3 lower_left_corner(-2., -1., -1.);
    Vec3 horizontal(4., 0., 0.);
    Vec3 vertical(0., 2., 0.);
    Vec3 origin(0., 0., 0.);

    out << "P3\n" << nx << " " << ny << "\n255\n";
    for(int j = ny ; j >= 0 ; --j)
    {
        for(int i = 0 ; i < nx ; ++i)
        {

            double u = double(i)/double(nx);
            double v = double(j)/double(ny);

            Ray r(origin, lower_left_corner + u * horizontal + v * vertical);
            Vec3 col = color(r);

            int ir = int(255.99*col.x());
            int ig = int(255.99*col.y());
            int ib = int(255.99*col.z());

            out << ir << " " << ig << " " << ib << endl;
        }
    }

    out.close();

    return 0;
}