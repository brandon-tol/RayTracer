#include "sphere.h"

namespace btoleda
{
    bool sphere::on_hit(const ray &r, double t_min, double t_max, hit_record &rec) const
    {
        vec3 oc = r.origin() - _m_center;
        auto a = r.direction().squaredNorm();
        auto half_b = oc.dot(r.direction());
        auto c = oc.squaredNorm() - _m_radius * _m_radius;
        auto discriminant = half_b * half_b - a * c;
        auto sqrt_discriminant = std::sqrt(discriminant);
        if (discriminant > 0)
        {
            auto t = (-half_b - sqrt_discriminant) / a;

            // Shorter t, implies that the ray is outside the sphere
            if (t < t_max && t > t_min)
            {
                rec.t = t;
                rec.hit_pos = r.at(rec.t);
                rec.normal = (rec.hit_pos - _m_center) / _m_radius;
                rec.mat = &_m_material;
                return true;
            }

            // Longer t, implies that the ray is inside the sphere
            t = (-half_b + sqrt_discriminant) / a;
            if (t < t_max && t > t_min)
            {
                rec.t = t;
                rec.hit_pos = r.at(rec.t);
                rec.normal = (_m_center - rec.hit_pos) / _m_radius;
                rec.mat = &_m_material;
                return true;
            }
        }
        return false;
    }

} // namespace RayTracer