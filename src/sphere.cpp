#include "sphere.h"

namespace RayTracer {
    bool sphere::on_hit(const ray& r, double t_min, double t_max, hit_record& rec) const
    {
        vec3 oc = r.origin() - _m_center;
        auto a = r.direction().squaredNorm();
        auto b = 2.0 * oc.dot(r.direction());
        auto c = oc.squaredNorm() - _m_radius * _m_radius;
        auto discriminant = b * b - 4.0 * a * c;
        if(discriminant > 0)
        {
            auto t = (-b - sqrt(discriminant)) / (2.0 * a);
            if(t < t_max && t > t_min)
            {
                rec.t = t;
                rec.hit_pos = r.at(rec.t);
                rec.normal = (rec.hit_pos - _m_center) / _m_radius;
                return true;
            }
            t = (-b + sqrt(discriminant)) / (2.0 * a);
            if(t < t_max && t > t_min)
            {
                rec.t = t;
                rec.hit_pos = r.at(rec.t);
                rec.normal = (rec.hit_pos - _m_center) / _m_radius;
                return true;
            }
        }
        return false;
    }

    vec3 sphere::random_in_unit_sphere()
    {
        vec3 p;
        do
        {
            p = 2.0 * vec3(drand48(), drand48(), drand48()) - vec3(1, 1, 1);
        } while(p.squaredNorm() >= 1.0);
        return p;
    }
} // namespace RayTracer