#define RELEASE_BUILD

#include "RayTracer.h"
#include "ray.h"
#include <simpleppm.h>
#include "ray_tracer.h"
#include "sphere.h"
#include "rectangle.h"
#include "point_light.h"
#include "area_light.h"

#ifndef RELEASE_BUILD
#include <iostream>
#endif

using namespace btoleda;

RayTracer::RayTracer(const nlohmann::json &j) : _m_json(j)
{
}

Eigen::Vector3d vec3_from_json(const nlohmann::json &j)
{
    return {j[0].get<double>(), j[1].get<double>(), j[2].get<double>()};
}

const material material_from_json(const nlohmann::json &j)
{
    if (j.contains("reflectance"))
    {
        return {vec3_from_json(j["ac"]), vec3_from_json(j["dc"]), vec3_from_json(j["sc"]), j["ka"].get<double>(), j["kd"].get<double>(), j["ks"].get<double>(), j["pc"].get<double>(), j["reflectance"].get<double>()};
    }
    else
    {
        return {vec3_from_json(j["ac"]), vec3_from_json(j["dc"]), vec3_from_json(j["sc"]), j["ka"].get<double>(), j["kd"].get<double>(), j["ks"].get<double>(), j["pc"].get<double>()};
    }
}

void RayTracer::run()
{
    if (!_m_json.contains("geometry") || !_m_json.contains("light") || !_m_json.contains("output"))
    {
#ifndef RELEASE_BUILD
        std::cout << "Please use a json which specifies geometry, light and output!" << std::endl;
#endif
        return;
    }
    scene s{};

    for (const auto &scene_obj : _m_json["geometry"])
    {
        if (scene_obj.contains("visible") && !scene_obj["visible"].get<bool>())
        {
            continue;
        }
        auto type = scene_obj["type"].get<std::string>();
        auto mat = material_from_json(scene_obj);
        if (type == "sphere")
        {
            point3 centre = vec3_from_json(scene_obj["centre"]);
            double radius{scene_obj["radius"].get<double>()};
            if (scene_obj.contains("transform"))
            {
                auto transform_data = scene_obj["transform"].get<std::vector<double>>();
                mat4 transform{transform_data.data()};
                vec4 homogeneous_center{centre.x(), centre.y(), centre.z(), 1.0};
                homogeneous_center = transform * homogeneous_center;
                centre = homogeneous_center.head(3) / homogeneous_center.w();
                vec4 homogeneous_radius{radius, radius, radius, 0.0};
                homogeneous_radius = transform * homogeneous_radius;
                radius = homogeneous_radius.x() + homogeneous_radius.y() + homogeneous_radius.z() / 3.0;
            }
            s.add_object(std::make_shared<sphere>(centre, radius, mat));
        }
        else if (type == "rectangle")
        {
            point3 p0 = vec3_from_json(scene_obj["p1"]);
            point3 p1 = vec3_from_json(scene_obj["p2"]);
            point3 p2 = vec3_from_json(scene_obj["p3"]);
            point3 p3 = vec3_from_json(scene_obj["p4"]);
            if (scene_obj.contains("transform"))
            {
                auto transform_data = scene_obj["transform"].get<std::vector<double>>();
                mat4 transform{transform_data.data()};
                vec4 homogeneous_p0{p0.x(), p0.y(), p0.z(), 1.0};
                vec4 homogeneous_p1{p1.x(), p1.y(), p1.z(), 1.0};
                vec4 homogeneous_p2{p2.x(), p2.y(), p2.z(), 1.0};
                vec4 homogeneous_p3{p3.x(), p3.y(), p3.z(), 1.0};
                homogeneous_p0 = transform * homogeneous_p0;
                homogeneous_p1 = transform * homogeneous_p1;
                homogeneous_p2 = transform * homogeneous_p2;
                homogeneous_p3 = transform * homogeneous_p3;
                p0 = homogeneous_p0.head(3) / homogeneous_p0.w();
                p1 = homogeneous_p1.head(3) / homogeneous_p1.w();
                p2 = homogeneous_p2.head(3) / homogeneous_p2.w();
                p3 = homogeneous_p3.head(3) / homogeneous_p3.w();
            }
            s.add_object(std::make_shared<rectangle>(p0, p1, p2, p3, mat));
        }
#ifndef RELEASE_BUILD
        else
        {
            std::cerr << "Unknown geometry type: " << type << std::endl;
        }
#endif
    }

    for (const auto &light : _m_json["light"])
    {
        if (light.contains("use") && !light["use"].get<bool>())
        {
            continue;
        }
        auto type = light["type"].get<std::string>();
        if (type == "point")
        {
            vec3 center = vec3_from_json(light["centre"]);
            vec3 id = vec3_from_json(light["id"]);
            vec3 is = vec3_from_json(light["is"]);
            if (light.contains("transform"))
            {
                auto transform_data = light["transform"].get<std::vector<double>>();
                mat4 transform{transform_data.data()};
                vec4 homogeneous_center{center.x(), center.y(), center.z(), 1.0};
                homogeneous_center = transform * homogeneous_center;
                center = homogeneous_center.head(3) / homogeneous_center.w();
            }
            s.add_light(std::make_shared<point_light>(id, is, center));
        }
        else if (type == "area")
        {
            point3 p0 = vec3_from_json(light["p1"]);
            point3 p1 = vec3_from_json(light["p2"]);
            point3 p2 = vec3_from_json(light["p3"]);
            point3 p3 = vec3_from_json(light["p4"]);
            vec3 id = vec3_from_json(light["id"]);
            vec3 is = vec3_from_json(light["is"]);
            const unsigned int n = light["n"].get<int>();
            if (light.contains("transform"))
            {
                auto transform_data = light["transform"].get<std::vector<double>>();
                mat4 transform{transform_data.data()};
                vec4 homogeneous_p0{p0.x(), p0.y(), p0.z(), 1.0};
                vec4 homogeneous_p1{p1.x(), p1.y(), p1.z(), 1.0};
                vec4 homogeneous_p2{p2.x(), p2.y(), p2.z(), 1.0};
                vec4 homogeneous_p3{p3.x(), p3.y(), p3.z(), 1.0};
                homogeneous_p0 = transform * homogeneous_p0;
                homogeneous_p1 = transform * homogeneous_p1;
                homogeneous_p2 = transform * homogeneous_p2;
                homogeneous_p3 = transform * homogeneous_p3;
                p0 = homogeneous_p0.head(3) / homogeneous_p0.w();
                p1 = homogeneous_p1.head(3) / homogeneous_p1.w();
                p2 = homogeneous_p2.head(3) / homogeneous_p2.w();
                p3 = homogeneous_p3.head(3) / homogeneous_p3.w();
            }
            if (light.contains("usecenter") && light["usecenter"].get<bool>())
            {
                s.add_light(std::make_shared<point_light>(area_light{p0, p1, p2, p3, id, is, n}));
            }
            else
            {
                s.add_light(std::make_shared<area_light>(p0, p1, p2, p3, id, is, n));
            }
        }
#ifndef RELEASE_BUILD
        else
        {
            std::cerr << "Unknown light type: " << type << std::endl;
        }
#endif
    }

    for (const auto &output : _m_json["output"])
    {
        ray_tracer_parameters params;
        auto output_filepath = output["filename"].get<std::string>();
        const int image_width = output["size"][0].get<int>();
        const int image_height = output["size"][1].get<int>();

        const double viewport_width = image_width;
        const double viewport_height = image_height;
        const double fov = output["fov"].get<int>();
        const double depth = viewport_height / (2.0 * std::tan(fov * M_PI / 360.0));

        s.set_ambient_intensity(vec3_from_json(output["ai"]));

        point3 eye_center = vec3_from_json(output["centre"]);
        vec3 up = vec3_from_json(output["up"]);
        vec3 lookat = vec3_from_json(output["lookat"]);

        eye e{viewport_width, viewport_height, depth, lookat, up, eye_center};
        s.set_eye(e);

        s.set_background(vec3_from_json(output["bkc"]));

        params.lighting = PHONG; // Default value
        params.globalillum = false;
        params.twosiderender = true; // Default value
        if (output.contains("twosiderender") && !output["twosiderender"].get<bool>())
        {
            params.twosiderender = false;
        }

        if (output.contains("globalillum") && output["globalillum"].get<bool>() && !(output.contains("maxbounces") && output["maxbounces"].get<int>() < 1))
        {
            params.globalillum = true;
            params.lighting = PATH_TRACING;
            if (output.contains("raysperpixel"))
            {
                auto rpp = output["raysperpixel"].get<std::vector<int>>();

                if (rpp.size() >= 3)
                {
                    params.raysperpixel[0] = rpp[0];
                    params.raysperpixel[1] = rpp[1];
                    params.raysperpixel[2] = rpp[2];
                }
                else if (rpp.size() == 2)
                {
                    params.raysperpixel[0] = params.raysperpixel[1] = rpp[0];
                    params.raysperpixel[2] = rpp[1];
                }
                else if (rpp.size() == 1)
                {
                    params.raysperpixel[0] = 1;
                    params.raysperpixel[1] = 1;
                    params.raysperpixel[2] = rpp[0];
                }
            }
            else
            {
                params.raysperpixel[0] = 10;
                params.raysperpixel[1] = 10;
                params.raysperpixel[2] = 10;
            }

            if (output.contains("maxbounces"))
            {
                params.max_bounces = output["maxbounces"].get<int>();
            }
            else
            {
                params.max_bounces = 3;
            }

            if (output.contains("probterminate"))
            {
                params.prob_terminate = output["probterminate"].get<double>();
            }
            else
            {
                params.prob_terminate = 0.3;
            }
        }
        else if (output.contains("antialiasing") && output["antialiasing"].get<bool>())
        {
            if (output.contains("raysperpixel"))
            {
                auto rpp = output["raysperpixel"].get<std::vector<int>>();
                if (rpp.size() == 3)
                {
                    params.raysperpixel[0] = rpp[0];
                    params.raysperpixel[1] = rpp[1];
                    params.raysperpixel[2] = rpp[2];
                }
                else if (rpp.size() == 2)
                {
                    params.raysperpixel[0] = params.raysperpixel[1] = rpp[0];
                    params.raysperpixel[2] = rpp[1];
                }
                else if (rpp.size() == 1)
                {
                    params.raysperpixel[0] = 1;
                    params.raysperpixel[2] = rpp[0];
                }
            }
            else
            {
                params.raysperpixel[0] = 10;
                params.raysperpixel[1] = 10;
                params.raysperpixel[2] = 1;
            }
        }
        else
        {
            params.raysperpixel[0] = 1;
            params.raysperpixel[1] = 1;
            params.raysperpixel[2] = 1;
        }

        ray_tracer rt{image_width, image_height, s, params};
        rt.generate_viewport();
        rt.print_viewport(output_filepath);
    }
}
