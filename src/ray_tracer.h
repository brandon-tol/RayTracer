#pragma once

#include "ray.h"
#include "eye.h"
#include "viewport.h"
#include "scene.h"

namespace btoleda
{
    class ray_tracer
    {
    private:
        viewport _m_viewport;
        const scene _m_scene;
        ray_tracer_parameters _m_params;

    public:
        void generate_viewport();
        inline ray_tracer(const int width, const int height, const scene &s, const ray_tracer_parameters &params)
            : _m_viewport{width, height}, _m_scene{s}, _m_params{params}
        {
        }

        void print_viewport(const std::string &target_filename) const;
    };
} // namespace btoleda