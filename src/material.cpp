#include "material.h"

namespace btoleda
{

    static vec3 s_reflect(const vec3 &incident, const vec3 &normal)
    {
        return -2 * normal.dot(incident) * normal + incident;
    }

    static vec3 s_random_in_unit_hemisphere(const vec3 &normal)
    {
        // 1. Generate a random point in the unit circle
        double x;
        double z;
        double len_squared;
        do
        {
            x = 2 * random_double() - 1.0;
            z = 2 * random_double() - 1.0;
            len_squared = x * x + z * z;
        } while (len_squared > 1.0);

        // 2. Project the point onto the unit hemisphere
        double y = std::sqrt(1.0 - len_squared);

        // 3. Create a coordinate system with the normal as the z-axis
        vec3 w = normal;
        vec3 u = w.cross(vec3{w.z(), w.x(), w.y()}).normalized();
        vec3 v = w.cross(u);

        // 4. Return the vector in the hemisphere
        return x * u + z * v + y * w;
    }

    const ray material::scatter(const point3 &impact, const vec3 &incident, const vec3 &normal) const
    {
        if (random_double() < 1.0)
            return ray{impact, s_random_in_unit_hemisphere(normal)};
        else
            return ray{impact, s_reflect(incident, normal)};
    }
} // namespace btoleda
