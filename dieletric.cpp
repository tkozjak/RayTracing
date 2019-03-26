
#include "dieletric.h"

dieletric::dieletric( QObject *parent, qreal refraction_indx, QRandomGenerator *random  ) : material(parent)
{
    m_refraction_indx = refraction_indx;
    m_random = random;
}

bool dieletric::scatter(const ray &in_ray, const hit_record &hit_rec, vec3 &attenuatino, ray &scattered){
    vec3 outward_normal;
    vec3 reflected = reflect( in_ray.direction(), hit_rec.normal );

    qreal ni_over_nt;

    attenuatino = vec3( 1.0, 1.0, 1.0 );

    qreal reflect_prob;
    qreal cosine;

    vec3 refracted;

    if( dot( in_ray.direction(), hit_rec.normal) > 0.0 ){
        outward_normal = -1 * hit_rec.normal; // NE FUNKCIONIRA NEGATIVE
        ni_over_nt = m_refraction_indx;

        cosine = m_refraction_indx * dot( in_ray.direction(), hit_rec.normal ) / in_ray.direction().length() ;
    }
    else{
        outward_normal = hit_rec.normal;
        ni_over_nt = 1.0 / m_refraction_indx;
        cosine = -dot(in_ray.direction(), hit_rec.normal);
    }

    if( refract( in_ray.direction(), outward_normal, ni_over_nt, refracted )){
//        scattered = ray( hit_rec.point, refracted );
        reflect_prob = schlick( cosine, m_refraction_indx );
    }
    else{
        scattered = ray( hit_rec.point, reflected, in_ray.time() );
        return false;
    }

    if( m_random->bounded(1.0) < reflect_prob ){
        scattered = ray( hit_rec.point, reflected, in_ray.time() );
    }
    else {
        scattered = ray( hit_rec.point, refracted, in_ray.time() );
    }
    return true;
}

qreal dieletric::schlick(qreal cosine, qreal ref_idx)
{
    qreal r0 = ( 1-ref_idx) / ( 1+ ref_idx );
    r0 = r0*r0;

    return r0 + ( 1- r0) * qPow( (1-cosine), 5.0 );

}

bool dieletric::refract(const vec3 &vector, const vec3 &n, qreal ni_over_nt, vec3 &refracted)
{

    vec3 uv = unit_vector( vector );
    qreal dt = dot( uv, vector );

    qreal discriminant = 1.0 - ni_over_nt * ni_over_nt * ( 1 - dt*dt );

    if( discriminant > 0 ){
        refracted = ni_over_nt*(uv - n*dt)-n*qSqrt(discriminant);
        return true;
    }
    else
        return false;

}

vec3 dieletric::reflect(const vec3 &view_vector, const vec3 &normal)
{
    return view_vector - 2 * dot( view_vector, normal ) * normal;
}
