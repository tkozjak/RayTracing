#include "scenemodel.h"
#include "main_scene.h"

SceneModel::SceneModel(QObject *parent)
    : QAbstractListModel(parent),
      m_scene(nullptr)
{

}


QHash<int, QByteArray> SceneModel::roleNames() const
{
    //    qDebug() <<"Role names called!";

    QHash<int, QByteArray> roles;

    roles[EntityNameRole] = "name";
    roles[EntityTypeRole] = "type";
    roles[SpherePositionRole] = "position";
    roles[SphereRadiusRole] = "radius";

    return roles;
}

int SceneModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if ( parent.isValid() || !m_scene )
        return 0;

    //    qDebug() <<"Row count function called :" << m_scene->entities().size();
    return m_scene->entities().size();

}


QVariant SceneModel::data(const QModelIndex &index, int role) const
{
    //    qDebug() << "Data called!";

    if (!index.isValid() || !m_scene )
        return QVariant();

    // get data item that our model wants to display with view
    const hitable_qentity *entity = m_scene->entities().at(index.row());

    // roles of our data item
    // some roles are standard roles but we use only user defined roles
    switch(role){
    case EntityNameRole:
        return QVariant(entity->getEntityName());
    case EntityTypeRole:
        return QVariant(entity->getEntityType());
    case SphereRadiusRole:
        return QVariant( entity->getRadius());
    case SpherePositionRole:
        return static_cast<qsphere*>( m_scene->entities().at(index.row()) )->getPosition();
    }

    return QVariant();
}

bool SceneModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
        qDebug() << "Set data called!";

    if(!m_scene)
        return false;

    hitable_qentity *current_entity = m_scene->entities().at(index.row());

    // change data item's roles
    switch(role){
    case EntityNameRole:
        current_entity->setEntityName( value.toString() );
        break;
    case EntityTypeRole:
        current_entity->setEntityType( (entity_type)value.toInt() );
        break;
    case SphereRadiusRole:
        current_entity->setRadius( value.toReal() );
        break;
        //    case SpherePositionRole:
        //        return QVariant(QVector3D(1.0, 1.0, -1.0));
        //        return QVariant("Default postion");
        //        return QVariant( (qsphere*)current_entity->getPosition());
        //        break;
    }

    if ( m_scene->setEntityAt( index.row(), current_entity ) ) {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags SceneModel::flags(const QModelIndex &index) const
{
    //    qDebug() << "Flags called!";

    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}


// get an actual class that contains data
main_scene *SceneModel::scene() const
{
    return m_scene;
}

// connect scene model with an actual class that contains data
void SceneModel::setScene(main_scene *scene)
{
    beginResetModel(); //IMPORTANT!

    if(m_scene)
        m_scene->disconnect(this);

    m_scene = scene;

    qDebug() << "Scene connected!";

    if(m_scene){
        connect(m_scene, &main_scene::preEntityAppended, this, [=]() {
            const int index = m_scene->entities().size();

            //            qDebug() << "Pre-append row count :" << index;
            beginInsertRows(QModelIndex(), index, index);

        } );

        connect(m_scene, &main_scene::postEntityAppended, this, [=]() {
            endInsertRows();

            //            const int index = m_scene->entities().size();
            //            qDebug() << "Post-append row count :" << index;

        } );

        connect(m_scene, &main_scene::preEntityRemoved, this, [=]( int index ) {
            beginRemoveRows(QModelIndex(), index, index);
        } );

        connect(m_scene, &main_scene::postEntityRemoved, this, [=]() {
            endRemoveRows();
        } );
    }

    endResetModel();
}

