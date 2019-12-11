#ifndef SCENEMODEL_H
#define SCENEMODEL_H

#include <QAbstractListModel>
#include <QDebug>

// forward declaration of our main scene object
class main_scene;


class SceneModel : public QAbstractListModel
{
    Q_OBJECT

    // we assign pointer to our scene in this porperty in qml
    Q_PROPERTY(main_scene *scene READ scene WRITE setScene)

public:
    explicit SceneModel(QObject *parent = nullptr);

    // custom data roles
    enum dataItem_roles {
        EntityNameRole = Qt::UserRole+1,
        EntityTypeRole,
        SpherePositionRole
    };

//    Q_INVOKABLE QString testFunction( int row ){
//        QModelIndex index;
//        index.
//    }

    // hash that maps role/enum to role name in qml
    virtual QHash<int, QByteArray> roleNames() const override;


    // this function returns row count - or item count in model/submodel
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    // this function returns data to view based on the index and role
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;


    // this function adds/modifies data    
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;


    // get/set functions that connect this model with an object that holds actuall data
    main_scene *scene() const;
    void setScene(main_scene *scene);

private:
    main_scene *m_scene;
};

#endif // SCENEMODEL_H
