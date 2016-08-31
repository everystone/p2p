#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QString>
#include <QStandardItemModel>
#include "typedefs.h"
#include "networkwrapper.h"
#include "settingsdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


public slots:
    void AddSystemMessage(QString);
    void DisplayErrorMsgBox(QString);
    void AddConnection(QString);

signals:
    //void SystemMessageSignal(QString);

private slots:
    void on_actionConnect_triggered();

    void on_actionSettings_triggered();

private:
    Ui::MainWindow *ui;
    NetworkWrapper *m_network;
    QStandardItemModel *m_messagesModel;
    QStandardItemModel *m_connectionsModel;
    SettingsDialog *m_settings;

};

#endif // MAINWINDOW_H
