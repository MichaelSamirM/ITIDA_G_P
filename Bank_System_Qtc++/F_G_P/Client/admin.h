#ifndef ADMIN_H
#define ADMIN_H

#include "client.h"


class Admin : public Client
{
public:
    explicit Admin();
<<<<<<< HEAD
    void AdminStart(bool);//admin
    void ViewAccount();//common
    void GetAccNo();//common
    void ViewBankDatabase();//admin
    void RecieveUserData();//admin
    void Deleteuser();//admin
    void UpdateUser();//admin
    void ViewTransactionHistory();//common
    void sendrequesttoserver(QString request);//admin
=======
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
>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb
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
<<<<<<< HEAD
        QDataStream inStream;;;
protected:
        QString a_username;
        QString n_username,n_age,n_accountnumber,n_password,n_balance;
};

#endif
=======
        QDataStream inStream;

};

#endif // ADMIN_H
>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb
