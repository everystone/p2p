#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QString>
#include <QStandardItemModel>
#include "client.h"
#include "typedefs.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public ICallbacks
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void OnConnect(std::string);
    void OnDisconnect(std::string);

public slots:
    void AddSystemMessage(QString);

signals:
    void SystemMessageSignal(QString);

private:
    Ui::MainWindow *ui;
    Client *m_client;
    QStandardItemModel *m_messagesModel;
    QStringList m_systemMessages;

};

#endif // MAINWINDOW_H
