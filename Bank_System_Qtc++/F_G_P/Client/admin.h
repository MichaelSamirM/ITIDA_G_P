#ifndef ADMIN_H
#define ADMIN_H

#include "client.h"


class Admin : public Client
{
public:
    explicit Admin();
    void AdminStart(bool);
    void ViewAccount();
    void GetAccNo();
    void ViewBankDatabase();
    void RecieveUserData(QString choice,QString UserName);
    void CreateNewUser();
    void Deleteuser();
    void UpdateUser();
    void ViewTransactionHistory();
    void sendrequesttoserver(QString request);
    bool Login();

signals:
public slots:
    void connectToHost(QString host,quint16 port);
    void disconnect();
protected slots:
    void connected();
    void disconnected();
    void error(QAbstractSocket::SocketError socketerror);
    void stateChanged(QAbstractSocket::SocketState socketstate);
    void readyRead();
private:
        QString _Adminname,_AdminPass,_AdminPassWord,_Balane,_Age;
        QTcpSocket socket;
        QDataStream outStream;
        QDataStream inStream;

};

#endif // ADMIN_H
