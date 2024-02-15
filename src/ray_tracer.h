#pragma once

#include "structures.h"
#include "ray.h"
#include "eye.h"
#include "viewport.h"
#include "scene.h"

namespace RayTracer {
    class ray_tracer {
    private:
        eye _m_eye;
        viewport _m_viewport;
        scene _m_scene;
    public:
        void generate_viewport();
        // FIXME: Temporary constructor
        ray_tracer(int width, int height)
            : _m_eye(double(width), double(height), 20.0, vec3(-1, 0, 0), vec3(0, 1, 0), point3(0, 0, 0)),
              _m_viewport(width, height)
        {}

        void print_viewport() const;
    };
} // namespace RayTracer