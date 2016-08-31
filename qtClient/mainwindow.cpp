#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Setup UI
    this->m_messagesModel = new QStandardItemModel(this);
    ui->systemMessagesListView->setModel(this->m_messagesModel);

    // Setup Network
    this->m_network = new NetworkWrapper(2222);

    // Connect signals from network wrapper
    QObject::connect(this->m_network, SIGNAL(ConnectSignal(QString)), this, SLOT(AddSystemMessage(QString)));
    QObject::connect(this->m_network, SIGNAL(DisconnectSignal(QString)), this, SLOT(AddSystemMessage(QString)));
    QObject::connect(this->m_network, SIGNAL(ErrorSignal(QString)), this, SLOT(DisplayErrorMsgBox(QString)));
}
void MainWindow::AddSystemMessage(QString msg){
    this->m_messagesModel->setItem(m_messagesModel->rowCount(),new QStandardItem(msg));
}

void MainWindow::DisplayErrorMsgBox(QString text)
{
    QMessageBox mBox;
    mBox.setText(text);
    mBox.show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
