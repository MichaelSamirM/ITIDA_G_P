#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QMetaEnum>
#include<QTextStream>


class Client : public QObject
{
    Q_OBJECT
public:
   explicit Client(QObject *parent = nullptr);
   virtual void GetAccNo()=0;
   virtual void ViewAccount()=0;
   virtual void ViewTransactionHistory()=0;
   virtual void sendrequesttoserver(QString request)=0;
   virtual bool Login()=0;

 protected:
    QString     _type;
    QString     _request;
    QString     _flag;
    QVariant    _respond;
    QString     _accountnumber;
    QString     _AllDataBase;
    quint32     _AccountBalance;
};

#endif // CLIENT_H
