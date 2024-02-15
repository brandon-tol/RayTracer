#include "scene.h"

namespace RayTracer
{

    color3 scene::trace(const ray& r) const
    {
        hit_record rec;
        if(on_hit(r, 0.001, MAXFLOAT, rec))
        {
           return 0.5 * color3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
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
        for(int i = 0; i < _m_list_count; i++)
        {
            if(_m_objects[i]->on_hit(r, t_min, closest_so_far, rec))
            {
                hit_anything = true;
                closest_so_far = rec.t;
            }
        }
        return hit_anything;
    }
} // namespace RayTracer