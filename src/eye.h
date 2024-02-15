#pragma once

#include "structures.h"

namespace RayTracer
{
    class eye {
    private:
        double _m_retina_width;
        double _m_retina_height;
        double _m_eye_depth;
        vec3 _m_retina_u;
        vec3 _m_retina_v;
        point3 _m_pupil;
        // could add something like _m_pupil_radius but for now we'll assume it's a point

            
    public:
        eye() = default;
        // retina_u and retina_v MUST be normalized
        eye(double retina_width, double retina_height, double eye_depth, const vec3 retina_u, const vec3 retina_v, const point3 pupil)
            : _m_retina_width(retina_width), _m_retina_height(retina_height), _m_eye_depth(eye_depth), _m_retina_u(retina_u), _m_retina_v(retina_v), _m_pupil(pupil) {}

        double retina_width() const { return _m_retina_width; }
        double retina_height() const { return _m_retina_height; }
        double eye_depth() const { return _m_eye_depth; }
        
        // The U vector is the horizontal vector of the retina from right to left
        vec3 retina_u() const { return _m_retina_u; }

        // The V vector is the vertical vector of the retina from bottom to top
        vec3 retina_v() const { return _m_retina_v; }

        // The W vector is the depth vector of the retina from the retina to the pupil 
        vec3 retina_w() const { return _m_retina_v.cross(_m_retina_u); }
        point3 pupil() const { return _m_pupil; }
        point3 point0() const { return _m_pupil - _m_retina_u * _m_retina_width * 0.5 - _m_retina_v * _m_retina_height * 0.5 - _m_eye_depth * retina_w(); }
        
    };    
} // namespace RayTracer
