#pragma once
#include <json.hpp>

class RayTracer
{
    private:
    
    const nlohmann::json _m_json;

    public:

    RayTracer(const nlohmann::json&);

    void run();
};