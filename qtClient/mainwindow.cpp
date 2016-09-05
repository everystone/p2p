#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qinputdialog.h>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Setup UI
    this->m_settings = new SettingsDialog(this);
    this->m_messagesModel = new QStandardItemModel(this);
    this->m_connectionsModel = new QStandardItemModel(this);
    ui->systemMessagesListView->setModel(this->m_messagesModel);
    ui->ConnectionsListView->setModel(this->m_connectionsModel);

}


// Status tab
void MainWindow::AddSystemMessage(QString msg){
    this->m_messagesModel->setItem(m_messagesModel->rowCount(),new QStandardItem(msg));
}
void MainWindow::AddConnection(QString ip){
    this->AddSystemMessage("New Connection: " + ip);
    QStandardItem *node = new QStandardItem();

    node->setIcon( QIcon(":/Icons/icons/netbook.png"));
    //node->setSizeHint(QSize(32,32));
    node->setText(ip);
    this->m_connectionsModel->appendRow(node);
    this->m_network->Ping();
}
void MainWindow::RemoveConnection(QString ip){
    this->AddSystemMessage(("Lost connection: "+ip));
    QList<QStandardItem*> list = this->m_connectionsModel->findItems(ip,Qt::MatchContains);
    for(int i=0;i<list.length();i++) {
        qDebug() << "item: " << list[i]->text();
    }
    if(list.length() > 0){
        this->m_connectionsModel->removeRow(list.first()->index().row());
    }else {
        qDebug() << "No matching connections found in list\n";
    }

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

void MainWindow::SetupNetwork(short port)
{
    // Setup Network
    this->m_network = new NetworkWrapper(port);
    //AddSystemMessage("Listening on " + port);
    // Connect signals from network wrapper
    QObject::connect(this->m_network, SIGNAL(ConnectSignal(QString)), this, SLOT(AddConnection(QString)));
    QObject::connect(this->m_network, SIGNAL(DisconnectSignal(QString)), this, SLOT(RemoveConnection(QString)));
    QObject::connect(this->m_network, SIGNAL(ErrorSignal(QString)), this, SLOT(DisplayErrorMsgBox(QString)));
}

// Main Menu Actions
void MainWindow::on_actionConnect_triggered()
{
    bool ok;
    QString ip = QInputDialog::getText(this, tr("Connect to peer.."),tr("Enter IP Address"), QLineEdit::Normal,"127.0.0.1", &ok);
    if (ok && !ip.isEmpty()) {
        this->m_network->ConnectToHost(ip);
    }
}

void MainWindow::on_actionSettings_triggered()
{
    this->m_settings->exec();
}
