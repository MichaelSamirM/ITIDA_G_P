#ifndef JSONFUNC_H
#define JSONFUNC_H

#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDateTime>

<<<<<<< HEAD
class JsonFunc:public QObject
{
public:
    JsonFunc(QObject * parent);

    bool authenticateUser(const QString,const QString, const QString);

    bool printObjectFields(const QString&,const QString&,const QString&, QString&);

    bool PrintDataBase(const QString &, QString &);

    bool UpdateBalance(const QString&,const QString& ,const QString& ,const  QString& );

    bool EditField(const QString &, const QString &,const QString &, const QString &);

    bool TransferAmount(const QString &,const QString &,const QString &,const QString &);

    bool checkObject(const QString& ,const QString&);

    bool deleteObject(const QString &,const QString &);

    bool SaveHistory(const QString ,const QString ,const QString &);

    QString ViewHistory( const QString &, const QString &,quint16 );

    bool AddNewObject(const QString &,QVariantMap ,const QString& );

    QString GetAccNo(const QString );

    QJsonObject _login;
=======
class JsonHandler
{
public:
    JsonHandler(QObject * parent);
    static bool authenticateUser(const QString &filename, const QString& username, const QString& password);
    static bool printObjectFields(const QString &fileName, const QString &objectName, const QString &request, QString &respond);
    static QString ViewUserField(const QString &fileName, const QString &objectName);
    static bool PrintDataBase(const QString &fileName, QString &DataBase);
    static bool updateFile(const QString& filename, const QString& Usersfilename, const QString& username, const QString& accountnumber, const QString& amount);
    static bool EditField(const QString &fileName, const QString &ObjectKey, const QString &FieldToChange, const QString &NewValue);
    static bool TransferAmount(const QString &fileName,const QString &fromtransferaccount,const QString & totransferaccount, const QString &transferamount);
    static bool checkObject(const QString& filename, const QString& keyValue);
    static bool deleteObject(const QString &filePath, const QString &objectKey);
    static bool SaveHistory(QString fileName, QString username,const QString &amount);
    static QString ViewHistory(const QString &fileName, const QString &username,quint16 count);
    static bool AddNewObject(const QString &fileName, QVariantMap newObject,const QString& NewObjectName);




>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb
};

#endif // JSONFUNC_H
