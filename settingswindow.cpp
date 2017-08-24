#include "settingswindow.h"
#include "ui_settingswindow.h"

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
                ui->tLogFile->text()
                );
}
