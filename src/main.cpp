#include "ray_tracer.h"
#include "sphere.h"

using namespace RayTracer;

int main()
{
    const int width = 800;
    const int height = 400;
    const double depth = 200.0;

    eye e(double(width), double(height), depth, point3(-1, 0, 0), point3(0, 1, 0), vec3(0, 0, 0));
    
    scene s(e);
    s.add_object(std::make_shared<sphere>(point3(0, 0, 1), 0.5));
    s.add_object(std::make_shared<sphere>(point3(0, -100.5, 1), 100));
    ray_tracer rt(width, height, s, 100);
    rt.generate_viewport();
    rt.print_viewport("test.ppm");
    return 0;
}