#pragma once
#include "core.h"
#include "ray.h"
#include "i_hittable.h"

namespace btoleda
{

    class scene_light
    {
    protected:
        inline scene_light(const color3 &id, const color3 &is) : _m_id{id}, _m_is{is} {}
        inline virtual ~scene_light() = default;

    public:
        inline const color3 &id() const { return _m_id; }
        inline const color3 &is() const { return _m_is; }

    private:
        color3 _m_id;
        color3 _m_is;
    };
} // namespace btoleda
