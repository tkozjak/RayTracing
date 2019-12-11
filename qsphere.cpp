#include "qsphere.h"


qsphere::qsphere( QString name, QObject *parent, vec3 center_1, vec3 center_2, qreal in_t_01, qreal in_t_02, qreal radius, material *in_material) : hitable_qentity(parent)
{
    m_entityName = name;

    m_time_01 = in_t_01;
    m_time_02 = in_t_02;

    m_center_01 = center_1;
    m_center_02 = center_2;
    m_radius = radius;

    m_p_material = in_material;
}

bool qsphere::hit(const ray &in_ray, qreal t_min, qreal t_max, hit_record &record) const
{
    vec3 o_to_c = in_ray.origin() - center( in_ray.time() );

    qreal a = dot( in_ray.direction(), in_ray.direction());
    qreal b = dot( o_to_c, in_ray.direction() );
    qreal c = dot( o_to_c, o_to_c ) - m_radius * m_radius;
    qreal discriminant = b*b - a*c;

    if( discriminant > 0 ){

        qreal temp = ( -b - qSqrt(discriminant) ) / a ;

        if( temp < t_max && temp >t_min ){
            record.t = temp;
            record.point = in_ray.point_at_parameter(record.t);
            record.normal = (record.point - center( in_ray.time() ) )/m_radius;
            record.p_mat = m_p_material;
            return true;
        }
        temp = ( -b + qSqrt(discriminant) ) / a ;
        if( temp < t_max && temp >t_min ){
            record.t = temp;
            record.point = in_ray.point_at_parameter(record.t);
            record.normal = (record.point - center( in_ray.time() ) )/m_radius;
            record.p_mat = m_p_material;
            return true;
        }
    }
    return false;
}

vec3 qsphere::center(qreal time) const
{
    return m_center_01 + ( ( time - m_time_01 ) / ( m_time_02 - m_time_01 ) ) * ( m_center_02 - m_center_01 );
}
