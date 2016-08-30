#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QString>
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

private:
    Ui::MainWindow *ui;
    Client *m_client;

};

#endif // MAINWINDOW_H
