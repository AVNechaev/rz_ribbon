#include "ribbonmodel.h"

RibbonModel::RibbonModel(size_t depth_) :
    depth(depth_)
{

}

int RibbonModel::rowCount(const QModelIndex&) const
{
//TODO
    return 0;
}

int RibbonModel::columnCount(const QModelIndex&) const
{
//    TODO
    return 0;
}

QVariant RibbonModel::data(const QModelIndex &, int) const
{
//    TODO
    return QString();
}

void RibbonModel::on_fire(FireData)
{
//TODO
}
