#include "metal.h"

metal::metal(QObject *parent, const vec3 &albedo, QRandomGenerator *random) : material(parent)
{
    m_random = random;
    m_albedo = albedo;
}

vec3 metal::reflect(const vec3 &view_vector, const vec3 &normal)
{
    return view_vector - 2 * dot( view_vector, normal ) * normal;
}

bool metal::scatter(const ray &in_ray, const hit_record &hit_rec, vec3 &attenuation, ray &scattered)
{
    vec3 reflected = reflect( unit_vector( in_ray.direction()), hit_rec.normal );
    scattered = ray( hit_rec.point, reflected );
    attenuation = m_albedo;
    return( dot( scattered.direction(), hit_rec.normal) > 0 );
}
