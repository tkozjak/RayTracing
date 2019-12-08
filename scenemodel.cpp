#include "scenemodel.h"
#include "main_scene.h"

SceneModel::SceneModel(QObject *parent)
    : QAbstractListModel(parent),
      m_scene(nullptr)
{
    qDebug() << "Roles";
    qDebug() << "Entity name role: " << EntityNameRole;
    qDebug() << "Entity type role: " << EntityTypeRole;
}


QHash<int, QByteArray> SceneModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[EntityNameRole] = "name";
    roles[EntityTypeRole] = "type";
    roles[SpherePositionRole] = "position";
    return roles;
}

int SceneModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !m_scene )
        return 0;

    // FIXME: Implement me!
    return main_scene().entities().size();
//    return 10;
}


QVariant SceneModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !m_scene )
        return QVariant();

    hitable_qentity *entity = m_scene->entities().at(index.row());

    qDebug() << "new entity: " << entity;

    // FIXME: Implement me!
    switch(role){
    case EntityNameRole:
        return QVariant(entity->getEntityName());
    case EntityTypeRole:
        return QVariant(entity->getEntityType());
    case SpherePositionRole:
        return QVariant(QVector3D(1.0, 1.0, -1.0));
//        return QVariant("Default postion");
//        return static_cast<qsphere*>( main_scene().entities().at(index.row()) )->getPosition();
    }

    return QVariant();
}

bool SceneModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!m_scene)
        return false;

    //"TO DO: EVERYTHING HERE"

    if (data(index, role) != value) {
        // FIXME: Implement me!
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags SceneModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me!
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

    if(m_scene){
        connect(m_scene, &main_scene::preEntityAppended, this, [=]() {
            const int index = m_scene->entities().size();
            qDebug() << "Appending model rows: " << index;
            beginInsertRows(QModelIndex(), index, index);
        } );

        connect(m_scene, &main_scene::postEntityAppended, this, [=]() {
            endInsertRows();
//            rowCount();
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

