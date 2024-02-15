#include "ray_tracer.h"

using namespace RayTracer;

int main()
{
    ray_tracer rt(500, 250);
    rt.generate_viewport();
    rt.print_viewport();
    return 0;
}