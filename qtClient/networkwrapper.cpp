#include "networkwrapper.h"
#include "client.h"

NetworkWrapper::NetworkWrapper(short port){
    this->m_client = new Client(port, this);
}

void NetworkWrapper::OnConnect(std::string ip){
    QString msg = QString("%1").arg(ip.c_str());
    emit ConnectSignal(msg);
    std::cout << "OnConnect: " << ip << std::endl;
}

void NetworkWrapper::OnDisconnect(std::string ip){
    std::cout << ip << " Disconnected." << std::endl;
    QString msg = QString("%1").arg(ip.c_str());
    emit DisconnectSignal(msg);
}

void NetworkWrapper::OnError(std::string err){
    QString msg = QString("%1").arg(err.c_str());
    emit ErrorSignal(msg);
}

void NetworkWrapper::ConnectToHost(QString host)
{
    std::string str = host.toStdString();
    const char* p = str.c_str();
    this->m_client->connect(p, 2222);
}
void NetworkWrapper::Ping(){
    this->m_client->ping();
}
