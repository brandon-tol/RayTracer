#include "rectangle.h"

namespace btoleda
{
    bool rectangle::on_hit(const ray& r, double t_min, double t_max, hit_record& rec) const
    {
        return _m_t1.on_hit(r, t_min, t_max, rec) || _m_t2.on_hit(r, t_min, t_max, rec);
    }
} // namespace btoleda
