#ifndef RIBBONMODEL_H
#define RIBBONMODEL_H

#include <QAbstractTableModel>
#include "firedata.h"

class RibbonModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    RibbonModel(size_t depth);
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &parent, int) const override;


public slots:
    void on_fire(FireData data);

private:
    size_t depth;
};

#endif // RIBBONMODEL_H
