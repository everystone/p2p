#ifndef NETWORKWRAPPER_H
#define NETWORKWRAPPER_H

#include <QObject>
#include "typedefs.h"
#include "client.h"
class NetworkWrapper : public QObject, ICallbacks
{
    Q_OBJECT
public:
    //explicit NetworkWrapper(QObject *parent = 0);
    NetworkWrapper(short port);
    void OnConnect(std::string);
    void OnDisconnect(std::string);
signals:
    void ConnectSignal(QString);
    void DisconnectSignal(QString);

public slots:

private:
Client *m_client;
};

#endif // NETWORKWRAPPER_H
