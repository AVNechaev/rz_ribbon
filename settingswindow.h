#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QDialog>
#include "settings.h"

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsWindow(const Settings* settings, QWidget *parent = 0);
    ~SettingsWindow();

    void updateSettings(Settings* settings) const;
private:
    Ui::SettingsWindow *ui;
};

#endif // SETTINGSWINDOW_H
