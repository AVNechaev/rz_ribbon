#include "ribbonmodel.h"

RibbonModel::RibbonModel(int depth_, QObject *parent) :
    QAbstractTableModel(parent),
    depth(depth_)
{

}

int RibbonModel::rowCount(const QModelIndex&) const
{
    return depth; //return as much data as possible
    //return storage.size();
}

int RibbonModel::columnCount(const QModelIndex&) const
{
    return 1;
}

QVariant RibbonModel::data(const QModelIndex& index, int role) const
{
    switch(role)
    {
    case Qt::DisplayRole:
        return extract_data(index);
    default:
        return QVariant();
    }
}

void RibbonModel::on_fire(FireData msg)
{
    static const QVector<int> affectedRole {Qt::DisplayRole};

    if(storage.size() >= depth)
        storage.pop_back();
    storage.push_front(msg);
    emit dataChanged(createIndex(0,0), createIndex(storage.size() - 1, 0));
}

QVariant RibbonModel::extract_data(const QModelIndex &index) const
{
    int row = index.row();
    if(row >= storage.size()) return QVariant();

    const FireData& data = storage.at(row);
    QString trunc_name = data.pattern_name;
    if(trunc_name.size() > 40)
    {
        trunc_name.truncate(35);
        trunc_name.append("...");
    }
    return QString(trunc_name + "\n" + data.instr_name + " " + data.fire_time);
}
