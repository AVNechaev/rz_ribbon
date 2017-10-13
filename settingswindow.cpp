#include "settingswindow.h"
#include "ui_settingswindow.h"
#include <QTimeZone>
#include <QDebug>

QString tz2string(const QTimeZone tz)
{
    return QString(tz.id()) + " (" + tz.displayName(QTimeZone::GenericTime, QTimeZone::OffsetName) + ")";
}

SettingsWindow::SettingsWindow(const Settings* settings, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);
    ui->tServer->setText(settings->getServer());
    ui->tPort->setValue(settings->getPort());
    ui->tLogin->setText(settings->getLogin());
    ui->tPasswd->setText(settings->getPasswd());
    ui->bShowNotifications->setChecked(settings->isShow_notifications());
    ui->bShowRibbon->setChecked(settings->isShow_ribbon());
    ui->bWriteLog->setChecked(settings->isWrite_log());
    ui->tLogFile->setText(settings->getLogfile());
    ui->cmbTimeZones->clear();
    for(auto tz_it : QTimeZone::availableTimeZoneIds(QLocale::Russia).toSet()) //remove duplicates
    {
        QTimeZone zone(tz_it);
        ui->cmbTimeZones->addItem(tz2string(zone), tz_it);
        //qDebug() << tz_it << "-" << zone.displayName(QTimeZone::GenericTime);
    }
    ui->cmbTimeZones->setCurrentText(tz2string(settings->getTimezone()));
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}

void SettingsWindow::updateSettings(Settings *settings) const
{
    settings->set(
                ui->tLogin->text(),
                ui->tPasswd->text(),
                ui->tServer->text(),
                ui->tPort->value(),
                ui->bShowNotifications->checkState() == Qt::Checked,
                ui->bShowRibbon->checkState() == Qt::Checked,
                ui->bWriteLog->checkState() == Qt::Checked,
                ui->tLogFile->text(),
                ui->cmbTimeZones->currentData().toByteArray()
                );
}
