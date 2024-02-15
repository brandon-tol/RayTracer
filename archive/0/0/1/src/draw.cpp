#include <iostream>
#include <Eigen/Eigen>
#include <simpleppm.h>

#include "draw.h"

namespace RayTracer {
    using color = Eigen::Vector3d;

    void draw(std::vector<ray>& rays, const int WIDTH, const int HEIGHT)
    {
        std::vector<double> buffer(WIDTH * HEIGHT * 3);
        
        for (int i = 0; i < rays.size(); i++)
        {
            color c = rays[i].get_color();
            buffer[3*i] = c.x();
            buffer[3*i + 1] = c.y();
            buffer[3*i + 2] = c.z();
        }
        save_ppm("test.ppm", buffer, WIDTH, HEIGHT);
    }
} // namespace RayTracer