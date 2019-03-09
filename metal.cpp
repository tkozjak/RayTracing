#include "metal.h"

metal::metal(QObject *parent, const vec3 &albedo, qreal fuzz, QRandomGenerator *random) : material(parent)
{
    if( fuzz < 1 )
        m_fuzz = fuzz;

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
    scattered = ray( hit_rec.point, reflected + m_fuzz * random_in_unit_sphere()   );
    attenuation = m_albedo;
    return( dot( scattered.direction(), hit_rec.normal) > 0 );
}

vec3 metal::random_in_unit_sphere()
{
    vec3 random_reflection_vector;
    do{
        random_reflection_vector = 2.0 * vec3( m_random->bounded(1.0), m_random->bounded(1.0),m_random->bounded(1.0) ) - vec3( 1.0, 1.0, 1.0 );

    }
    while( (random_reflection_vector.squaredLength() >= 1.0) );

    return random_reflection_vector;
}
