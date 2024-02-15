#include "ray_tracer.h"
#include "sphere.h"

using namespace RayTracer;

int main()
{
    const int width = 800;
    const int height = 400;
    const double depth = 200.0;

    eye e(double(width), double(height), depth, point3(-1, 0, 0), point3(0, 1, 0), vec3(0, 0, 0));
    const size_t scene_size = 2;
    const scene_object* list[scene_size];
    list[0] = new sphere(point3(0, 0, 1), 0.5);
    list[1] = new sphere(point3(0, -100.5, 1), 100);
    
    scene s(e, list, scene_size);
    ray_tracer rt(width, height, s);
    rt.generate_viewport();
    rt.print_viewport("test.ppm");
    return 0;
}