#ifndef RIBBONMODEL_H
#define RIBBONMODEL_H

#include <QAbstractTableModel>
#include "firedata.h"
#include <QFontMetrics>
#include <QList>
#include <QTimeZone>

class Settings;
class RibbonModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    RibbonModel(int depth, QFontMetrics metrics_, QObject *parent = Q_NULLPTR);
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;


public slots:
    void on_fire(FireData msg);
    void settings_changed(const Settings* settings);

private:
    QFontMetrics metrics;
    int depth;
    QList<FireData> storage;
    const QTimeZone tz;
    QTimeZone tz_msk;

    QVariant extract_data(const QModelIndex& index) const;
};

#endif // RIBBONMODEL_H
