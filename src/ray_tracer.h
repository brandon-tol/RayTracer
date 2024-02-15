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
    public:
        void generate_viewport();
        // FIXME: Temporary constructor
        ray_tracer(int width, int height, scene s)
            : _m_viewport(width, height), _m_scene(s)
        {}

        void print_viewport(std::string target_filename) const;
    };
} // namespace RayTracer