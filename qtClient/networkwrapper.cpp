#include "networkwrapper.h"
#include "client.h"

NetworkWrapper::NetworkWrapper(short port){
    this->m_client = new Client(port, this);
}

void NetworkWrapper::OnConnect(std::string ip){
    QString msg = QString("New Connection: %1..").arg(ip.c_str());
    emit ConnectSignal(msg);
    std::cout << "Connection from: " << ip << std::endl;
}

void NetworkWrapper::OnDisconnect(std::string ip){
    std::cout << ip << " Disconnected." << std::endl;
    QString msg = QString("%1 Disconnected").arg(ip.c_str());
    emit DisconnectSignal(msg);
}

void NetworkWrapper::OnError(std::string err){
    QString msg = QString("%1").arg(err.c_str());
    emit ErrorSignal(msg);
}
