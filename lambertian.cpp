
#include "lambertian.h"

lambertian::lambertian(QObject *parent, const vec3 &albedo, QRandomGenerator *random) : material(parent)
{
    m_random = random;
    m_albedo = albedo;
}

bool lambertian::scatter(const ray &in_ray, const hit_record &hit_rec, vec3 &attenuation, ray &scattered)
{
    vec3 target = hit_rec.point + hit_rec.normal + random_in_unit_sphere();
    scattered = ray( hit_rec.point , target - hit_rec.point, in_ray.time() );
    attenuation = m_albedo;

    return true;
}

vec3 lambertian::random_in_unit_sphere()
{
    vec3 random_reflection_vector;
    do{
        random_reflection_vector = 2.0 * vec3( m_random->bounded(1.0), m_random->bounded(1.0),m_random->bounded(1.0) ) - vec3( 1.0, 1.0, 1.0 );

    }
    while( (random_reflection_vector.squaredLength() >= 1.0) );

    return random_reflection_vector;
}

