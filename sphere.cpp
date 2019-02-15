#include "sphere.h"

sphere::sphere()
{

}

sphere::sphere(vec3 center, qreal radius) : m_center(center), m_radius(radius)
{

}

bool sphere::hit(const ray &in_ray, const qreal t_min, const qreal t_max, hit_record &record) const
{
    vec3 o_to_c = in_ray.origin() - m_center;

    qreal a = dot( in_ray.direction(), in_ray.direction());
    qreal b = dot( o_to_c, in_ray.direction() );
    qreal c = dot( o_to_c, o_to_c ) - m_radius * m_radius;
    qreal discriminant = b*b - a*c;

    if( discriminant > 0 ){

        qreal temp = ( -b - qSqrt(discriminant) ) / a ;

        if( temp < t_max && temp >t_min ){
            record.t = temp;
            record.point = in_ray.point_at_parameter(record.t);
            record.normal = (record.point - m_center)/m_radius;
            return true;
        }
        temp = ( -b + qSqrt(discriminant) ) / a ;
        if( temp < t_max && temp >t_min ){
            record.t = temp;
            record.point = in_ray.point_at_parameter(record.t);
            record.normal = (record.point - m_center)/m_radius;
            return true;
        }

    }
    return false;
}
