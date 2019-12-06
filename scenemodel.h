#ifndef SCENEMODEL_H
#define SCENEMODEL_H

#include <QAbstractListModel>

class SceneModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit SceneModel(QObject *parent = nullptr);

    // roles
    enum{
        EntityNameRole = Qt::UserRole + 1
    };


    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

private:
};

#endif // SCENEMODEL_H
