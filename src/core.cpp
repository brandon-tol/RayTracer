#include "core.h"

namespace btoleda
{
    double random_double()
    {
#ifdef WIN32
        return rand() / (RAND_MAX + 1.0);
#else
        return drand48();
#endif
    }

    ray_tracer_parameters::ray_tracer_parameters()
    {
        raysperpixel[0] = 1;
        raysperpixel[1] = 1;
        raysperpixel[2] = 1;
        twosiderender = true;
        lighting = BLINN_PHONG;
        max_bounces = 0;
        prob_terminate = 0.0;
    }
} // namespace btoleda
