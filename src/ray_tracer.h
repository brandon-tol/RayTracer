#pragma once

#include "structures.h"
#include "ray.h"
#include "eye.h"
#include "viewport.h"
#include "scene.h"

namespace RayTracer {
    class ray_tracer 
    {
    private:
        viewport _m_viewport;
        scene _m_scene;
        unsigned int _m_antialiasing_samples;
    public:
        void generate_viewport();
        // FIXME: Temporary constructor
        ray_tracer(int width, int height, scene s, unsigned int antialiasing_samples = 1)
            : _m_viewport(width, height), _m_scene(s), _m_antialiasing_samples(antialiasing_samples)
        {}

        void print_viewport(std::string target_filename) const;
    };
} // namespace RayTracer