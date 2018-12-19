#include<iostream>
#include<fstream>
#include "../include/ray.h"

using namespace std;

bool hit_sphere(const Vec3& center, double radius, const Ray& r)
{
    Vec3 oc = r.origin() - center;
    double a = dot(r.direction(), r.direction());
    double b = 2. * dot(oc, r.direction());
    double c = dot(oc, oc) - radius*radius;
    double discriminant = b*b - 4.*a*c;
    return discriminant > 0;
}

Vec3 color(const Ray& r)
{
    if(hit_sphere(Vec3(0.,0.,-1.), 0.5, r))
        return Vec3(1.,0.,0.);
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