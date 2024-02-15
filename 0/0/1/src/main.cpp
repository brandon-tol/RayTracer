#include "draw.h"
#include "camera.h"

#include <iostream>

using namespace RayTracer;

int main(int argc, char const *argv[])
{
    const int SCALE = 75;
    const int WIDTH = 16 * SCALE;
    const int HEIGHT = 9 * SCALE;
    const double focal_length = 40.0;
    // const double viewport_height = 2.0;
    // const double viewport_width = 16.0 / 9.0 * viewport_height;

    // auto viewport_u = Eigen::Vector3d(viewport_width, 0, 0);
    // auto viewport_v = Eigen::Vector3d(0, -viewport_height, 0);


    camera cam(Eigen::Vector3d(0, 0, 0), Eigen::Vector3d(0, 0, 1), Eigen::Vector3d(0, 1, 0));

    std::vector<ray> rays(WIDTH * HEIGHT);

    Eigen::Vector3d pixel_zero = cam.pinhole() - cam.view_direction() * focal_length - cam.up() * 0.5 * HEIGHT + cam.right() * 0.5 * WIDTH;

    for(int j = 0; j < HEIGHT; j++)
    {
        for(int i = 0; i < WIDTH; i++)
        {
            Eigen::Vector3d origin = pixel_zero + j * cam.up() - i * cam.right();
            rays[j * WIDTH + i] = ray(origin, cam.pinhole() - origin);
            // std::cout << "Ray " << j * WIDTH + i << " origin: " << rays[j * WIDTH + i].origin() << " direction: " << rays[j * WIDTH + i].direction() << "color: " << rays[j * WIDTH + i].get_color() << std::endl;
        }
    }

    draw(rays, WIDTH, HEIGHT);
}
