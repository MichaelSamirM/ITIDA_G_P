#ifndef SERVER_H
#define SERVER_H


#include    <QObject>
#include    <QDebug>
#include    <QAbstractSocket>
#include    <QTcpSocket>
#include    <QTcpServer>
#include    "jsonfunc.h"
<<<<<<< HEAD


class Server : public JsonFunc
{
    Q_OBJECT
public:
    explicit Server(JsonFunc *parent = nullptr);
=======
//#include    <QFile>
//#include    <QJsonDocument>
//#include    <QJsonArray>
//#include    <QJsonObject>
//#include    <QIODevice>
//#include    <QIODeviceBase>

class Server : public JsonHandler
{
    Q_OBJECT
public:
    explicit Server(JsonHandler *parent = nullptr);
>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb

    void HandlClienterequest(QString request,QString role);
    quint32 generateUniqueNumber(const QString& uniqueString);


signals:
public slots:
    void start();
    void quit();
    void newConnection();
    void disconnected();
    void OnreadyRead();

private:
    QTcpServer server;
<<<<<<< HEAD
    QString _type,_request,_respond;
    QString _path;
    QString _historyfile;
    QString _usersfile, _adminsfile;
=======
    QString _type,_request;
    QString m_path;
    QString m_historyfile;
    QString m_usersfile, m_adminsfile;
>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb
 protected:

};

#endif // SERVER_H
