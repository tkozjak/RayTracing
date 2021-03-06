#include "main_scene.h"


main_scene::main_scene(QObject *parent) : QObject(parent)
{
//    m_scene_model = new SceneModel(this);
//    m_scene_model->setScene(this);

    m_random = new QRandomGenerator;
    m_applicationPath = QGuiApplication::applicationDirPath();    

    // qspheres
    hitable_qentity *SQ1 = new qsphere( "crvena", this, vec3( 1.5, 0.0, -1.0), vec3( 1.5, 0.0, -1.0), 0.0, 100.0, 0.5, new lambertian( this, vec3(1.0, 0.1, 0.1 ), m_random ));
    hitable_qentity *SQ2 = new qsphere( "podloga", this, vec3( 0.0, -100.5, -1.0), vec3( 0.0, -100.5, -1.0), 0.0, 100.0, 100.0,  new lambertian( this, vec3(1.0, 1.0, 1.0 ), m_random ));
    hitable_qentity *SQ3 = new qsphere( "brza", this, vec3( 1.1, 0.0, -1.0), vec3( -1.1, 0.0, -1.0), 0.0, 100.0, 0.5,  new metal( this, vec3(0.2, 0.9, 0.1 ), 0.3, m_random ));
    hitable_qentity *SQ4 = new qsphere( "prozirna", this, vec3( -0.95, -0.1, -1.2), vec3( -0.95, -0.1, -1.2), 0.0, 100.0, 0.3,  new dieletric( this, 1.4, m_random ));

    m_p_hitable_qentities_list.append(SQ1);
    m_p_hitable_qentities_list.append(SQ2);
    m_p_hitable_qentities_list.append(SQ3);
    m_p_hitable_qentities_list.append(SQ4);

    // default camera
    vec3 lookfrom( 1, 55.5, 5 );
    vec3 lookat( 0.3, 0, -1 );
    qreal dist_to_focus = ( lookfrom-lookat ).length();
    qreal aperture = 0.0;

    m_camera = new camera( this, lookfrom, lookat, vec3( 0, 1, 0 ), 20, qreal(nx)/qreal(ny), aperture, dist_to_focus, 0.0, 100.0, m_random  );

}

void main_scene::draw_scene()
{
    QFile myfile(m_applicationPath + "/" + "example.ppm");
    if(myfile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Writing DEBUG started";

        // We're going to streaming text to the file
        QTextStream txt_myfile(&myfile);

        // vectors that describe our viewing plane
        vec3 lower_left_corner( -2.0, -1.0, -1.0 );
        vec3 horizontal( 4.0, 0.0, 0.0 );
        vec3 vertical( 0.0, 2.0, 0.0 );
        vec3 origin( 0.0, 0.0, 0.0 );

        txt_myfile <<"P3\n" << nx << " " << ny << "\n255\n";
        for(int j = ny-1; j >=0; j--){
            for(int i=0; i<nx; i++){

                qDebug() << "Ray :" << j << ", " << i;

                vec3 color( 0.0 ,0.0, 0.0 );
                for( int s=0; s < ns; s++){
                    qreal u = qreal( i + m_random->bounded(1.0)) / qreal(nx);
                    qreal v = qreal( j + m_random->bounded(1.0)) / qreal(ny);

                    ray primary_ray = m_camera->get_ray( u, v );

                    color = color + ray_to_color( primary_ray, 0 );
                }

                color = color / qreal(ns);

                // gamma 2.0
                //                color = vec3(qSqrt(color[0]), qSqrt(color[1]), qSqrt(color[2]));

                int ir = int(255.99*color[0]);
                int ig = int(255.99*color[1]);
                int ib = int(255.99*color[2]);

                txt_myfile << ir << " " << ig << " " << ib << "\n";
            }
        }

        myfile.close();
        qDebug() << "Writing DEBUG finished";

        emit renderComplete();
    }
}

void main_scene::draw_debug_scene()
{

    QFile myfile("example.ppm");
    if(myfile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Writing DEBUG started";

        // We're going to streaming text to the file
        QTextStream txt_myfile(&myfile);

        // vectors that describe our viewing plane
        vec3 lower_left_corner( -2.0, -1.0, -1.0 );
        vec3 horizontal( 4.0, 0.0, 0.0 );
        vec3 vertical( 0.0, 2.0, 0.0 );
        vec3 origin( 0.0, 0.0, 0.0 );

        txt_myfile <<"P3\n" << nx << " " << ny << "\n255\n";
        for(int j = ny-1; j >=0; j--){
            for(int i=0; i<nx; i++){

                qDebug() << "Ray :" << j << ", " << i;

                vec3 color( 0.0 ,0.0, 0.0 );
                for( int s=0; s < ns; s++){
                    qreal u = qreal( i + m_random->bounded(1.0)) / qreal(nx);
                    qreal v = qreal( j + m_random->bounded(1.0)) / qreal(ny);

                    ray primary_ray = m_camera->get_ray( u, v );

                    color = color + ray_to_color( primary_ray, 0 );
                }

                color = color / qreal(ns);

                // gamma 2.0
                //                color = vec3(qSqrt(color[0]), qSqrt(color[1]), qSqrt(color[2]));

                int ir = int(255.99*color[0]);
                int ig = int(255.99*color[1]);
                int ib = int(255.99*color[2]);

                txt_myfile << ir << " " << ig << " " << ib << "\n";
            }
        }

        myfile.close();
        qDebug() << "Writing DEBUG finished";

        emit renderComplete();
    }


}

bool main_scene::setEntityAt(int index, hitable_qentity *entity)
{
    if(index < 0 || index >= m_p_hitable_qentities_list.size() )
        return false;

    // replace entity (TO DO: HANDLE THIS BETTER)

    const hitable_qentity *current_entity = m_p_hitable_qentities_list.at(index);

    if( entity->getEntityName() == current_entity->getEntityName() && entity->getEntityType() == current_entity->getEntityType() )
        return false;

    m_p_hitable_qentities_list[index] = entity;

    return true;
}

QVector<hitable_qentity*> main_scene::entities() const
{
    return m_p_hitable_qentities_list;
}

// main function that returns color of hit point
vec3 main_scene::ray_to_color(const ray &in_ray, int bounce) const
{
    //    return vec3( 1.0, 0.0, 0.0 );
    hit_record hit_rec;

    if( any_hit( in_ray, m_t_min, m_t_max, hit_rec ) ){

        ray scattered_ray;
        vec3 attenuation;

        if( bounce < m_bounces && hit_rec.p_mat->scatter( in_ray, hit_rec, attenuation, scattered_ray ) ){
            return attenuation * ray_to_color( scattered_ray, bounce+1 );
        }
        else{
            return vec3( 0.0, 0.0, 0.0 );
        }
    }
    else{
        vec3 sun_direction = unit_vector( vec3( 1.0, 0.6, 1.5 ) );
        vec3 unit_direction = unit_vector( in_ray.direction());
        qreal t = 0.5 * ( unit_direction.y() + 1.0 );
        qreal factor = dot( sun_direction, unit_direction );
        if( factor < 0.0 ){
            factor = 0.0;
        }
        return(( 1.0 - t ) * vec3( 1.0, 1.0, 1.0 ) + t * vec3( 0.5, 0.7, 1.0 )) * (factor+0.35);

        //        vec3 unit_direction = unit_vector( in_ray.direction() );
        //        qreal t = 0.5 * (unit_direction.y() + 1.0 );
        //        return ( 1.0 - t ) * vec3( 1.0, 1.0, 1.0 ) + t * vec3( 0.5, 0.7, 1.0 );
    }
}

bool main_scene::any_hit(const ray &in_ray, const qreal t_min, const qreal t_max, hit_record &record ) const
{
    hit_record temp_hit_record;

    bool hit_anything = false;

    qreal closest_so_far = t_max;

    // iterate over list opf hitable entites return true if contditions of 'hit' are satisfied
    for( int i = 0; i < m_p_hitable_qentities_list.count(); i++ ){
        if( m_p_hitable_qentities_list.at(i)->hit( in_ray, t_min, closest_so_far, temp_hit_record)){
            hit_anything = true;
            closest_so_far = temp_hit_record.t;
            record = temp_hit_record;
        }
    }
    return hit_anything;
}

void main_scene::resetCamera( vec3 in_position, vec3 in_lookAt )
{
    vec3 lookfrom = in_position;
    vec3 lookat = in_lookAt;

    delete m_camera;


    qreal dist_to_focus = ( lookfrom-lookat ).length();
    qreal aperture = 0.0;

    m_camera = new camera( this, lookfrom, lookat, vec3( 0, 1, 0 ), 70, qreal(nx)/qreal(ny), aperture, dist_to_focus, 0.0, 100.0, m_random  );

}

void main_scene::appendEntity()
{
    // emit signal to model that we are about to append our list
    // pre
    emit preEntityAppended();

    // model calls data() somewhere here - it fills model with data items for view to display

    // create default sphere
    vec3 pos_vec(25 - m_random->bounded(50.0), 1 - m_random->bounded(2.0), 25 - m_random->bounded(50.0));
    qreal rad = 0.1 + m_random->bounded(2.0);
    hitable_qentity *defaultEntity = new qsphere( "default", this, /*vec3( 1.5, 0.0, -1.0)*/pos_vec, /*vec3( 1.5, 0.0, -1.0)*/pos_vec, 0.0, 100.0, rad, new lambertian( this, vec3(1.0, 0.1, 0.1 ), m_random ));
    m_p_hitable_qentities_list.append(defaultEntity);


    // emit signal to model that appended our list
    emit postEntityAppended();

}

void main_scene::removeEntityAt(int index)
{
    if(index >= 0 || index >= m_p_hitable_qentities_list.size() ){
        emit preEntityRemoved(index);
        m_p_hitable_qentities_list.removeAt(index);
        emit postEntityRemoved();
    }
}
