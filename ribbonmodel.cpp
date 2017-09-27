#include "ribbonmodel.h"

#include <QDateTime>

RibbonModel::RibbonModel(int depth_, QFontMetrics metrics_, QObject *parent) :
    QAbstractTableModel(parent),    
    depth(depth_),
    metrics(metrics_),
    tz(0),
    tz_msk("Europe/Moscow")
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
    QDateTime dt = QDateTime::fromString(data.fire_time, "yyyy-MM-dd'T'HH:mm:ss.000Z");
    dt.setTimeZone(tz);
    QString trunc_name = data.pattern_name;
    //-5 == ".FXCM"
    QString second_line = data.instr_name.left(data.instr_name.size() - 5) + " " + data.timeframe + " " + dt.toTimeZone(tz_msk).toString("HH:mm:ss");

//TODO: remove 280
    return QString(metrics.elidedText(trunc_name, Qt::ElideRight, 430) + "\n" + metrics.elidedText(second_line, Qt::ElideRight, 430));
}
