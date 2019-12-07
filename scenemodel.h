#ifndef SCENEMODEL_H
#define SCENEMODEL_H

#include <QAbstractListModel>
#include <QDebug>

class SceneModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit SceneModel(QObject *parent = nullptr);

    // custom data roles
    enum{
        EntityNameRole = Qt::UserRole,
        EntityTypeRole = Qt::UserRole+1
    };

    // hash that maps role/enum) to role name in qml
    virtual QHash<int, QByteArray> roleNames() const override;


    // this function returns row count - or item count in model/submodel
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    // this function returns data to view based on the index and role
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;


    // this function adds/modifies data
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

private:
};

#endif // SCENEMODEL_H
