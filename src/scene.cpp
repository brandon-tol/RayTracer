#include "scene.h"
#include <limits>
#include "point_light.h"
#include "area_light.h"

namespace btoleda
{
    const vec3 scene::_reflect(const vec3 &incident, const vec3 &normal)
    {
        return 2 * normal.dot(incident) * normal - incident;
    }

    const color3 scene::_path_trace(const ray &r, const int max_bounces_left, const double prob_terminate, bool twosiderender) const
    {
        hit_record rec;
        if (max_bounces_left <= 0 || random_double() < prob_terminate)
        {
            return _get_color(r, DIFFUSE, twosiderender);
        }
        else if (on_hit(r, 0.001, std::numeric_limits<double>::max(), rec))
        {
            // propogate the ray
            auto normal = rec.normal;
            if (twosiderender && r.direction().dot(normal) > 0.0)
            {
                normal = -normal;
            }
            ray new_ray{rec.mat->scatter(rec.hit_pos, r.direction(), normal)};
            return new_ray.direction().dot(normal) * _path_trace(new_ray, max_bounces_left - 1, prob_terminate, twosiderender).cwiseProduct(rec.mat->k_diffuse() * rec.mat->diffuse_color());
            //  + 0.5 *_get_color(r, DIFFUSE, twosiderender); (adds some time but brightens the image)
        }
        else
        {
            // repeat the try
            return _path_trace(r, max_bounces_left - 1, prob_terminate, twosiderender);
        }
    }

    const color3 scene::trace(const ray &r, ray_tracer_parameters params) const
    {
        if (params.lighting == PATH_TRACING)
            return _path_trace(r, params.max_bounces, params.prob_terminate, params.twosiderender).cwiseMin(1.0);
        else if (params.lighting == BLINN_PHONG)
            return _get_color(r, (color_type)(AMBIENT | DIFFUSE | SPECULAR | HALF_APPROX), params.twosiderender);
        else if (params.lighting == PHONG)
            return _get_color(r, (color_type)(AMBIENT | DIFFUSE | SPECULAR), params.twosiderender);
        else
            return _m_background;
    }

    const color3 scene::_get_color(const ray &r, color_type ct, bool twosiderender) const
    {
        hit_record rec;
        if (on_hit(r, 0.001, std::numeric_limits<double>::max(), rec))
        {
            vec3 ambient_light = {0.0, 0.0, 0.0};
            vec3 diffuse_light = {0.0, 0.0, 0.0};
            vec3 specular_light = {0.0, 0.0, 0.0};
            if (ct & AMBIENT)
            {
                ambient_light = rec.mat->k_ambient() * rec.mat->ambient_color();
            }

            if (ct & (DIFFUSE | SPECULAR))
            {
                auto normal = rec.normal;
                if (twosiderender && r.direction().dot(normal) > 0.0)
                {
                    normal = -normal;
                }
                for (const auto &light_source : _m_lights)
                {
                    if (const std::shared_ptr<point_light> pl = std::dynamic_pointer_cast<point_light>(light_source))
                    {
                        ray new_ray = ray{rec.hit_pos, pl->center() - rec.hit_pos};
                        hit_record rec2;
                        if (on_hit(new_ray, 0.001, 1, rec2))
                        {
                            continue;
                        }
                        else
                        {
                            auto incident = (pl->center() - rec.hit_pos).normalized();
                            auto n_dot_l = std::max(normal.dot(incident), 0.0);
                            if (ct & DIFFUSE)
                                diffuse_light += (rec.mat->k_diffuse() * n_dot_l * pl->id());
                            if ((ct & SPECULAR) && n_dot_l > 0.0)
                            {
                                if (ct & HALF_APPROX)
                                {
                                    auto halfway = (incident - r.direction()).normalized();
                                    auto cos_beta = normal.dot(halfway);
                                    if (cos_beta > 0.0)
                                    {
                                        auto spec_light = rec.mat->k_specular() * std::pow(cos_beta, rec.mat->pc()) * pl->is();
                                        specular_light += spec_light;
                                    }
                                }
                                else
                                {
                                    auto cos_alpha = -(2 * n_dot_l * normal - incident).dot(r.direction());
                                    if (cos_alpha > 0.0)
                                    {
                                        auto spec_light = rec.mat->k_specular() * std::pow(cos_alpha, rec.mat->pc()) * pl->is();
                                        specular_light += spec_light;
                                    }
                                }
                            }
                        }
                    }
                    else if (const std::shared_ptr<area_light> al = std::dynamic_pointer_cast<area_light>(light_source))
                    {
                        int n = al->n();
                        for (int i = 0; i < n; i++)
                        {
                            for (int j = 0; j < n; j++)
                            {
                                point_light pl{*al, i, j};
                                {
                                    ray new_ray = ray{rec.hit_pos, pl.center() - rec.hit_pos};
                                    hit_record rec2;
                                    if (on_hit(new_ray, 0.001, 1, rec2))
                                    {
                                        continue;
                                    }
                                    else
                                    {
                                        auto incident = (pl.center() - rec.hit_pos).normalized();
                                        auto n_dot_l = std::max(normal.dot(incident), 0.0);
                                        if (ct & DIFFUSE)
                                            diffuse_light += (rec.mat->k_diffuse() * n_dot_l * pl.id());
                                        if ((ct & SPECULAR) && n_dot_l > 0.0)
                                        {
                                            if (ct & HALF_APPROX)
                                            {
                                                auto halfway = (incident - r.direction()).normalized();
                                                auto cos_beta = normal.dot(halfway);
                                                if (cos_beta > 0.0)
                                                {
                                                    auto spec_light = rec.mat->k_specular() * std::pow(cos_beta, rec.mat->pc()) * pl.is();
                                                    specular_light += spec_light;
                                                }
                                            }
                                            else
                                            {
                                                auto cos_alpha = -(2 * n_dot_l * normal - incident).dot(r.direction());
                                                if (cos_alpha > 0.0)
                                                {
                                                    auto spec_light = rec.mat->k_specular() * std::pow(cos_alpha, rec.mat->pc()) * pl.is();
                                                    specular_light += spec_light;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            return (ambient_light + diffuse_light.cwiseProduct(rec.mat->diffuse_color()) + specular_light.cwiseProduct(rec.mat->specular_color())).cwiseMin(1.0);
        }
        else
        {
            return _m_background;
        }
    }

    bool scene::on_hit(const ray &r, double t_min, double t_max, hit_record &rec) const
    {
        bool hit_anything = false;
        double closest_so_far = t_max;
        for (auto &elem : _m_objects)
        {
            if (elem->on_hit(r, t_min, closest_so_far, rec))
            {
                hit_anything = true;
                closest_so_far = rec.t;
            }
        }
        return hit_anything;
    }
} // namespace btoleda