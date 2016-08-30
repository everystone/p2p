#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->m_client = new Client(2222);
    this->m_client->set_connect_delegate(this);
}

void MainWindow::OnConnect(std:: string ip){
    QMessageBox msgBox;
    //msgBox.setText(QString::fromUtf8(ip.c_str()));
    msgBox.setText("Connected");
    msgBox.exec();
}
void MainWindow::OnDisconnect(std:: string ip){

}

MainWindow::~MainWindow()
{
    delete ui;
}
