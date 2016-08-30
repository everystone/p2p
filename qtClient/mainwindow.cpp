#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->m_messagesModel = new QStandardItemModel(this);
    this->m_systemMessages.append("Init");
    this->m_client = new Client(2222);
    this->m_client->set_connect_delegate(this);

    ui->systemMessagesListView->setModel(this->m_messagesModel);

    this->m_messagesModel->setItem(0,new QStandardItem(QString("Init..")));

    // Connect signals
    QObject::connect(this, SIGNAL(SystemMessageSignal(QString)), this, SLOT(AddSystemMessage(QString)));
}
void MainWindow::AddSystemMessage(QString msg){
    this->m_messagesModel->setItem(m_messagesModel->rowCount(),new QStandardItem(msg));
}

void MainWindow::OnConnect(std:: string ip){
    //QMessageBox msgBox;
    //msgBox.setText(QString::fromUtf8(ip.c_str()));
    //msgBox.setText("Connected");
    //msgBox.exec();

    QString msg = QString("New Connection: %1..").arg(ip.c_str());
    emit SystemMessageSignal(msg);
    std::cout << "Connection from: " << ip << std::endl;
}
void MainWindow::OnDisconnect(std:: string ip){
    std::cout << ip << " Disconnected." << std::endl;
    QString msg = QString("%1 Disconnected").arg(ip.c_str());
    emit SystemMessageSignal(msg);
}

MainWindow::~MainWindow()
{
    delete ui;
}
