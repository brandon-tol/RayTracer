#include "triangle.h"

namespace btoleda
{
    bool triangle::on_hit(const ray &r, double t_min, double t_max, hit_record &rec) const
    {
        vec3 e1 = _m_p1 - _m_p0;
        vec3 e2 = _m_p2 - _m_p0;
        vec3 h = r.direction().cross(e2);
        double a = e1.dot(h);
        if (a > -0.0000001 && a < 0.0000001)
        {
            return false;
        }
        double f = 1 / a;
        vec3 s = r.origin() - _m_p0;
        double u = f * s.dot(h);
        if (u < 0.0 || u > 1.0)
        {
            return false;
        }
        vec3 q = s.cross(e1);
        double v = f * r.direction().dot(q);
        if (v < 0.0 || u + v > 1.0)
        {
            return false;
        }
        double t = f * e2.dot(q);
        if (t > t_min && t < t_max)
        {
            rec.t = t;
            rec.hit_pos = r.at(rec.t);
            rec.normal = normal();
            rec.mat = &_m_material;
            return true;
        }
        return false;
    }
} // namespace btoleda