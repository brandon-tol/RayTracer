#include "ray.h"

namespace RayTracer {
    bool hits_sphere(const ray* r, Eigen::Vector3d center, double radius)
    {
        Eigen::Vector3d oc = r->origin() - center;
        double a = r->direction().dot(r->direction());
        double b = 2.0 * oc.dot(r->direction());
        double c = oc.dot(oc) - radius*radius;
        double discriminant = b*b - 4*a*c;
        
        return (discriminant > 0);
    }

    Eigen::Vector3d ray::get_color() const
    {  
        return hits_sphere(this, Eigen::Vector3d(0, 15, 10), 6) ? Eigen::Vector3d(1, 0, 0) : Eigen::Vector3d(0, 0, 0);
    }
} // namespace RayTracer