#include "hitable_entites_list.h"

hitable_entites_list::hitable_entites_list()
{

}

bool hitable_entites_list::hit(const ray &in_ray, qreal t_min, qreal t_max, hit_record &record) const
{
    hit_record temp_hit_record;

    bool hit_anything = false;
    qreal closest_so_far = t_max;

    for( int i = 0; i < m_list_size; i++ ){
        if( m_list[i]->hit( in_ray, t_min, closest_so_far, temp_hit_record)){
            hit_anything = true;
            closest_so_far = temp_hit_record.t;
            record = temp_hit_record;
        }
    }
    return hit_anything;
}
