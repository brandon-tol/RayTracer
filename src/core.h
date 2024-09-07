#pragma once

#include <Eigen/Eigen>
#include <json.hpp>
#include <cstdlib>
#include <limits>
#include <memory>

#ifdef WIN32
#define _USE_MATH_DEFINES
#endif
#include <cmath>

#ifndef M_PI
#define M_PI 3.1415926535897932384626
#endif

namespace btoleda
{
    using color3 = Eigen::Vector3d;
    using point3 = Eigen::Vector3d;
    using vec3 = Eigen::Vector3d;
    using vec4 = Eigen::Vector4d;
    using mat4 = Eigen::Matrix4d;

    double random_double();

    enum lighting_type
    {
        PHONG,
        BLINN_PHONG,
        PATH_TRACING
    };

    enum color_type : uint8_t
    {
        AMBIENT = 0b001,
        DIFFUSE = 0b010,
        SPECULAR = 0b100,
        HALF_APPROX = 0b1000,
        SHOW_BACKGROUND = 0b10000
    };

    struct ray_tracer_parameters
    {
        int raysperpixel[3];
        bool antialiasing;
        bool twosiderender;
        bool globalillum;
        lighting_type lighting;
        uint32_t max_bounces;
        double prob_terminate;

        ray_tracer_parameters();
    };

} // namespace RayTracer