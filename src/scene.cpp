#include "scene.h"
#include "sphere.h"
#include <limits>

namespace RayTracer
{

    color3 scene::trace(const ray& r) const
    {
        hit_record rec;
        if(on_hit(r, 0.001, std::numeric_limits<double>::max(), rec))
        {
            vec3 target = rec.hit_pos + rec.normal + sphere::random_in_unit_sphere();
            return 0.5 * color3(trace(ray(rec.hit_pos, target - rec.hit_pos)));
        }
        else
        {
            vec3 unit_direction = r.direction().normalized();
            double t = 0.5 * (unit_direction.y() + 1.0);
            return (1.0 - t) * color3(1.0, 1.0, 1.0) + t * color3(0.5, 0.7, 1.0);
        }
        
    }

    bool scene::on_hit(const ray& r, double t_min, double t_max, hit_record& rec) const
    {
        bool hit_anything = false;
        double closest_so_far = t_max;
        for(auto elem : _m_objects)
        {
            if(elem->on_hit(r, t_min, closest_so_far, rec))
            {
                hit_anything = true;
                closest_so_far = rec.t;
            }
        }
        return hit_anything;
    }
} // namespace RayTracer