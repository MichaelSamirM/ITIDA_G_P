#ifndef USER_H
#define USER_H

#include "client.h"


class User : public Client
{
public:
    explicit User();
    void UserStart(bool);
    void TransferAmount();
    void MakeTransaction();
<<<<<<< HEAD
    void ViewAccount();//common
    void GetAccNo();//common
    void ViewTransactionHistory();//common
    void sendrequesttoserver(QString request);
    bool Login();//
=======
    void ViewAccount();
    void GetAccNo();
    void ViewTransactionHistory();
    void sendrequesttoserver(QString request);
    bool Login();
>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb
    quint8 UserOptions();
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
<<<<<<< HEAD
    QTcpSocket socket;
    QDataStream outStream;
    QDataStream inStream;
=======
        QTcpSocket socket;
>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb


protected:
        QString u_username;
};

#endif // USER_H
