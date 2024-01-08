#ifndef JSONFUNC_H
#define JSONFUNC_H

#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDateTime>

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




};

#endif // JSONFUNC_H
