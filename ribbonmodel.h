#ifndef RIBBONMODEL_H
#define RIBBONMODEL_H

#include <QAbstractTableModel>
#include "firedata.h"
#include <QList>

class RibbonModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    RibbonModel(int depth, QObject *parent = Q_NULLPTR);
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;


public slots:
    void on_fire(FireData msg);

private:
    int depth;
    QList<FireData> storage;

    QVariant extract_data(const QModelIndex& index) const;
};

#endif // RIBBONMODEL_H
