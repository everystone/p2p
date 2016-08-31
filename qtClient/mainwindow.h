#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QString>
#include <QStandardItemModel>
#include "typedefs.h"
#include "networkwrapper.h"

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

private:
    Ui::MainWindow *ui;
    NetworkWrapper *m_network;
    QStandardItemModel *m_messagesModel;
    QStandardItemModel *m_connectionsModel;

};

#endif // MAINWINDOW_H
