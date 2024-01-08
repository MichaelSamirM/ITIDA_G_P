#ifndef SERVER_H
#define SERVER_H


#include    <QObject>
#include    <QDebug>
#include    <QAbstractSocket>
#include    <QTcpSocket>
#include    <QTcpServer>
#include    "jsonfunc.h"
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
    QString _type,_request;
    QString m_path;
    QString m_historyfile;
    QString m_usersfile, m_adminsfile;
 protected:

};

#endif // SERVER_H
