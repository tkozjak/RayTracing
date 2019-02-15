#ifndef HITABLE_ENTITES_LIST_H
#define HITABLE_ENTITES_LIST_H

#include "hitable_entity.h"

class hitable_entites_list : public hitable_entity
{
public:
    hitable_entites_list();

    hitable_entites_list( hitable_entity **in_list, int in_size){ m_list = in_list; m_list_size = in_size;  }
    virtual bool hit( const ray &in_ray, qreal t_min, qreal t_max, hit_record &record ) const;


    hitable_entity **m_list;
    int m_list_size;
};

#endif // HITABLE_ENTITES_LIST_H
