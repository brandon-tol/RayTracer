#pragma once

#include <vector>
#include "ray.h"

namespace RayTracer
{
    void draw(std::vector<ray>& rays, const int WIDTH, const int HEIGHT);
} // namespace RayTracer
