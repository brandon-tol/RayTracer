#pragma once

#include <Eigen/Eigen>

namespace RayTracer {
    class ray {
    private:
        Eigen::Vector3d _m_origin;
        Eigen::Vector3d _m_direction;
    public:
        ray() {}
        ray(const Eigen::Vector3d& origin, const Eigen::Vector3d& direction)
            : _m_origin(origin), _m_direction(direction.normalized()) {}

        Eigen::Vector3d origin() const { return _m_origin; }
        Eigen::Vector3d direction() const { return _m_direction; }

        Eigen::Vector3d at(double t) const {
            return _m_origin + t*_m_direction;
        }

        Eigen::Vector3d get_color() const;
    };
}