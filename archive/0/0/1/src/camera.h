#pragma once
#include <Eigen/Eigen>

namespace RayTracer
{
    class camera
    {
    private:
        Eigen::Vector3d _m_pinhole;
        Eigen::Vector3d _m_view_direction;
        Eigen::Vector3d _m_up;
        Eigen::Vector3d _m_right;

    public:
        camera(Eigen::Vector3d pinhole, Eigen::Vector3d view_direction, Eigen::Vector3d up)
            : _m_pinhole(pinhole), _m_view_direction(view_direction.normalized()), _m_up(up.normalized()), _m_right(_m_up.cross(_m_view_direction)) {}

        Eigen::Vector3d pinhole() const { return _m_pinhole; }
        Eigen::Vector3d view_direction() const { return _m_view_direction; }
        Eigen::Vector3d up() const { return _m_up; }
        Eigen::Vector3d right() const { return _m_right; }
    };
} // namespace RayTracer
