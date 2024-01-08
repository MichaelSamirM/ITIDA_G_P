#include "jsonfunc.h"

JsonHandler::JsonHandler(QObject* parent) {
    QObject{parent};
}


bool JsonHandler::authenticateUser(const QString& filename, const QString& username, const QString& password) {
    // Load JSON file
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error: Cannot open users.json";
        return false;
    }

    // Read JSON data
    QByteArray fileData = file.readAll();
    file.close();

    // Parse JSON
    QJsonDocument FileDoc = QJsonDocument::fromJson(fileData);
    if (FileDoc.isNull()) {
        qDebug() << "Error: Failed to parse JSON data";
        return false;
    }

    // Check if the root element is an object
    if (!FileDoc.isObject()) {
        qDebug() << "Error: JSON data is not an object";
        return false;
    }

    QJsonObject UserObject = FileDoc.object();

    // Check if the username exists in the JSON object
    if (UserObject.contains(username) && UserObject[username].isObject()) {
        QJsonObject UserObject = UserObject[username].toObject();

        // Check if the password matches
        if (UserObject.contains("password") && UserObject["password"].toString() == password) {
            qDebug() << "User authenticated: " << username;
            return true;  // Authentication successful
        }
    }

    qDebug() << "User not found or incorrect password";
    return false;  // Authentication failed
}
bool JsonHandler::checkObject(const QString& filename, const QString& FieldValue) {
    // Load JSON file
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error: Cannot open users.json";
        return false;
    }

    // Read JSON data
    QByteArray fileData = file.readAll();
    file.close();

    // Parse JSON
    QJsonDocument fileDoc = QJsonDocument::fromJson(fileData);
    if (fileDoc.isNull()) {
        qDebug() << "Error: Failed to parse JSON data";
        return false;
    }

    // Check if the root element is an object
    if (!fileDoc.isObject()) {
        qDebug() << "Error: JSON data is not an object";
        return false;
    }

    QJsonObject usersObject = fileDoc.object();

    // Check if the username exists in the JSON object
    if (usersObject.contains(FieldValue) && usersObject[FieldValue].isObject())
    {
        return true;
    }

    qDebug() << "User not found or incorrect password";
    return false;  // Authentication failed
}


bool JsonHandler::printObjectFields(const QString &fileName, const QString &objectName, const QString &request, QString &respond)
{
    // bool ok =false;
    QFile file(fileName);
    if ( file.open(QIODevice::ReadOnly | QIODevice::Text) ) {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll());
        file.close();

        if (!jsonDoc.isNull() && jsonDoc.isObject()) {
            QJsonObject jsonObject = jsonDoc.object();

            // Check if the specified objectName exists
            if (jsonObject.contains(objectName) ) {
                QJsonObject targetObject = jsonObject.value(objectName).toObject();

                // ok = true;
                respond = targetObject[request].toString();
                return true;

            } else {
                qWarning() << "Object with name" << objectName << "not found in the JSON file.";
            }
        } else {
            qWarning() << "Failed to parse JSON data from" << fileName;
        }
    } else {
        qWarning() << "Failed to open file for reading:" << file.errorString();
    }
    return false;
}

QString JsonHandler::ViewUserField(const QString &fileName, const QString &objectName)
{
    QString account;
    QFile file(fileName);
    if ( file.open(QIODevice::ReadOnly | QIODevice::Text) ) {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll());
        file.close();

        if (!jsonDoc.isNull() && jsonDoc.isObject()) {
            QJsonObject jsonObject = jsonDoc.object();

            // Check if the specified objectName exists
            if (jsonObject.contains(objectName)) {
                QJsonObject targetObject = jsonObject.value(objectName).toObject();

                // Print the fields of the specified object
                account =  "usernamr:" + objectName + "\n"
                                                     "Account Number: " + targetObject["Account Number"].toString()+ "\n"
                                                                        "Full name: " + targetObject["fullname"].toString()+ "\n"
                                                                  "Age: " + targetObject["Age"].toString()+ "\n"
                                                             "Balance: " + targetObject["Balance"].toString();

                return account;

            } else {
                qWarning() << "Object with name" << objectName << "not found in the JSON file.";
            }
        } else {
            qWarning() << "Failed to parse JSON data from" << fileName;
        }
    } else {
        qWarning() << "Failed to open file for reading:" << file.errorString();
    }
    return "Can't find the Account";

}


bool JsonHandler::PrintDataBase(const QString &fileName, QString &DataBase)
{

    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open file";
        return false;
    }

    // Read all data from the file
    QByteArray fileData = file.readAll();

    // Parse the JSON data
    QJsonDocument filedoc = QJsonDocument::fromJson(fileData);

    // Check if the document is valid
    if (!filedoc.isNull())
    {
        // Convert JSON document to formatted string
        QString OutputFile = filedoc.toJson(QJsonDocument::Indented);
        // Print the entire JSON content
        qDebug().noquote() << "Contents of JSON file:";
        qDebug().noquote() << OutputFile;

        DataBase = OutputFile;
        return true;
    }
    else
    {
        qDebug() << "Failed to parse JSON document";
    }
    DataBase = "error";
    return false;

}

bool JsonHandler::EditField(const QString &fileName, const QString &ObjectKey, const QString &SpecificField, const QString &NewValue)
{
    // read json file
    QFile file(fileName);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        //Parse the JSON document from the file
        QJsonDocument FileDoc = QJsonDocument::fromJson(file.readAll());
        file.close();

        // Check if the JSON document is an object
        if(!FileDoc.isNull() && FileDoc.isObject())
        {
            // Create a new json object and save the old json object in it
            QJsonObject Obj = FileDoc.object();

            // Check if the specified object key exists and is an object
            if ( Obj.contains(ObjectKey) && Obj[ObjectKey].isObject() )
            {
                // Modify the new json object
                QJsonObject TheNewObject = Obj[ObjectKey].toObject();
                TheNewObject[SpecificField] = NewValue;

                // Update the original json object in the main json file
                Obj[ObjectKey] = TheNewObject ;

                // write the modifited json object to the main json file
                if( file.open(QIODevice::WriteOnly | QIODevice::Text) )
                {
                    QJsonDocument modifiedJsonDoc(Obj);
                    file.write(modifiedJsonDoc.toJson());
                    file.close();
                    qDebug() << "Field updated successfully.";
                    return true;
                }else {
                    qDebug() << "Error: Unable to open the file for writing.";
                }
            }else {
                qDebug() << "Error: Object key not found or not an object.";
            }


        } else {
            qDebug() << "Error: Invalid JSON document.";
        }
    }else {
        qWarning() << "Failed to open file for reading:" << file.errorString();
    }
    return false;

}


bool JsonHandler::updateFile(const QString& filename, const QString &Usersfilename, const QString& username,  const QString& accountnumber, const QString& amount) {
    bool ok = false;
    QString balance;
    QFile Usersfile(Usersfilename);
    qint32 Amount = amount.toInt(&ok);
    if(ok == true)
    {
        if ( Usersfile.open(QIODevice::ReadOnly | QIODevice::Text) ) {
            QJsonDocument jsonUsersDoc = QJsonDocument::fromJson(Usersfile.readAll());
            Usersfile.close();

            if (!jsonUsersDoc.isNull() && jsonUsersDoc.isObject()) {
                QJsonObject jsonUsersObject = jsonUsersDoc.object();

                // Check if the specified objectName exists
                if (jsonUsersObject.contains(username) ) {
                    QJsonObject targetObject = jsonUsersObject.value(username).toObject();
                    balance = targetObject["Balance"].toString();
                    if(Amount < 0)
                    {
                        if(balance.toInt() + Amount >= 0)
                        {
                            ok = SaveHistory( filename, username,amount);

                            if(ok == true)
                            {
                                qint32 NewBalance = balance.toInt() + Amount;
                                QString strValue = QString::number(NewBalance);
                                ok = EditField(Usersfilename, username, "Balance", strValue);
                                ok=true;
                            }
                            else
                            {
                                ok = false;
                                qDebug() << "cannot add to transaction history";
                            }

                        }
                        else
                        {
                            ok = false;
                        }
                    }
                    else
                    {
                        ok = SaveHistory( filename, username,amount);
                        if(ok == true)
                        {
                            qint32 NewBalance = balance.toInt() + Amount;
                            QString strValue = QString::number(NewBalance);
                            ok = EditField(Usersfilename, username, "Balance", strValue);
                            ok=true;
                        }
                        else
                        {
                            ok = false;
                            qDebug() << "cannot add to transaction history";
                        }

                    }

                } else {
                    qWarning() << "Object with name" << username << "not found in the JSON file.";
                    ok = false;
                    balance = "error";
                }
            } else {
                qWarning() << "Failed to parse JSON data from" << Usersfilename;
            }
        } else {
            qWarning() << "Failed to open file for reading:" << Usersfile.errorString();
        }
    }
    else{
        ok = false;
    }

    qDebug() << "done making transacyion" << ok;

    return ok;
}



QString JsonHandler::ViewHistory(const QString &fileName, const QString &username,quint16 count)
{
    QString result;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        result = "Error: Can't open the DataBase file";
    }

    // Read JSON data
    QByteArray jsonData = file.readAll();
    file.close();

    // Parse JSON
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
    if (jsonDoc.isNull()) {
        result = "Error: Failed to parse JSON data ";
    }

    // Check if the JSON document is an object
    if (!jsonDoc.isObject()) {
        result = "Error: JSON data is not an object";
    }
    QJsonObject usersObject = jsonDoc.object();

    if(usersObject.contains(username)&&usersObject[username].isObject())
    {

        QJsonObject  userObject = usersObject[username].toObject();
        if(!userObject.contains("Transaction History"))
        {
            result = "This user doesn't have transaction history";
            return result;
        }
        QJsonArray transactionHistoryArray = userObject["Transaction History"].toArray();
        int objectsToPrint = qMin(count, static_cast<quint16>(transactionHistoryArray.size()));
        for (int i = 0; i < objectsToPrint; ++i)
        {
            QJsonObject jsonObject = transactionHistoryArray.at(i).toObject();
            // Convert the object to a string and append it to the result
            result += QJsonDocument(jsonObject).toJson(QJsonDocument::Indented);

        }

        qDebug() << "Get history successfully";

    }
    return result;
}

bool JsonHandler::AddNewObject(const QString &fileName, QVariantMap newObject, const QString &NewObjectName)
{
    QFile file(fileName);
    //Check for opening the file in Read only mode && as Text file
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        // Read all file contnents and then parse it as a json document and then save it in a qjson document ...Read existing JSON data from the file
        QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll());
        // close file
        file.close();

        // Checking that json fileis successfully read and parsed && contains a valid json object
        if(!jsonDoc.isNull() && jsonDoc.isObject())
        {
            // Convert the JSON object to a QVariantMap
            QVariantMap jsonMap = jsonDoc.object().toVariantMap();

            // Add the new object to the QVariantMap
            jsonMap[NewObjectName] = newObject;

            // Convert the QVariantMap back to a JSON object
            QJsonObject jsonObj = QJsonObject::fromVariantMap(jsonMap);

            // Open the file for writing
            if (file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                // Write the modified JSON data back to the file
                file.write(QJsonDocument(jsonObj).toJson());
                file.close();
                qDebug() << "New object added to" << fileName;
                return true;
            }else {
                qWarning() << "Failed to open file for writing:" << file.errorString();
            }
        } else {
            qWarning() << "Failed to parse JSON data from" << fileName;
        }
    } else {
        qWarning() << "Failed to open file for reading:" << file.errorString();
    }
    return false;
}


bool JsonHandler::SaveHistory(QString fileName, QString username, const QString &amount)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Error: Can't open the DataBase file";
    }

    // Read JSON data
    QByteArray jsonData = file.readAll();

    // Parse JSON
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
    if (jsonDoc.isNull()) {
        qDebug() << "Error: Failed to parse JSON data ";
    }

    // Check if the root element is an object
    if (!jsonDoc.isObject()) {
        qDebug() << "Error: JSON data is not an object";
    }

    QJsonObject usersObject = jsonDoc.object();
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString dateTimeString = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");
    QJsonObject transactionObject;
    transactionObject["datetime"] = dateTimeString;
    transactionObject["details"] = amount;
    if(usersObject.contains(username)&&usersObject[username].isObject())
    {
        // QJsonObject  userObject = usersObject[username].toObject();

        qDebug() << "User exists";
    }
    else
    {
        QString objectname= username;
        usersObject[objectname] = QJsonObject();
        file.seek(0);
        file.write(QJsonDocument(usersObject).toJson());
    }
    QJsonObject  userObject = usersObject[username].toObject();

    if (!userObject.contains("Transaction History")) {
        // If not, create a new empty array for "Transaction History"
        userObject["Transaction History"] = QJsonArray();
    }

    // Get the existing "Transaction History" array
    QJsonArray transactionHistoryArray = userObject["Transaction History"].toArray();

    // Prepend the new transaction to the front of the array
    transactionHistoryArray.prepend(transactionObject);
    userObject["Transaction History"] = transactionHistoryArray;
    usersObject[username]=userObject;
    file.seek(0);
    file.write(QJsonDocument(usersObject).toJson());
    return true;
    file.close();
    return false;
}



bool JsonHandler::TransferAmount(const QString &fileName, const QString &fromUsername, const QString &toUsername, const QString &transferamount)
{
    bool ok = false;
    QString respond, respondto;
    qint32 Transferamount = transferamount.toInt();
    ok = printObjectFields(fileName, fromUsername, "Balance", respond );
    if(ok == true)
    {
        if(respond.toInt() - Transferamount > 0)
        {
            ok = printObjectFields(fileName, toUsername, "Balance", respondto );
            if(ok == true)
            {
                quint32 Respond = respond.toInt() - Transferamount;
                quint32 Respondto =respondto.toInt() + Transferamount;
                respond = QString::number(Respond);
                respondto = QString::number(Respondto);
                ok = EditField(fileName, fromUsername, "Balance", respond);
                if(ok == true)
                {
                    ok = EditField(fileName, toUsername, "Balance", respondto);
                    return ok;
                }
                else
                {
                    qInfo() << "Failed to open file for writing";
                }
            }
            else
            {
                qInfo() << "Failed to open file for reading";

            }
        }
        else
        {
            qInfo() << "Transfer amount id bigger than your balance";
        }

    }
    else
    {
        qInfo() << "Failed to open file for reading";
    }



    return ok;
}




bool JsonHandler::deleteObject(const QString &filePath, const QString &objectKey)
{
    // Step 1: Read the JSON file
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        qDebug() << "Error: Unable to open the file for reading.";
        // return;
    }

    // Parse the JSON document from the file
    QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll());
    file.close();

    // Step 2: Check if the JSON document is an object
    if (jsonDoc.isObject())
    {
        QJsonObject jsonObject = jsonDoc.object();

        // Step 3: Check if the specified object key exists
        if (jsonObject.contains(objectKey))
        {
            // Step 4: Remove the specified object from the main JSON object
            jsonObject.remove(objectKey);

            // Step 5: Write the modified JSON object back to the file
            if (file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                QJsonDocument modifiedJsonDoc(jsonObject);
                file.write(modifiedJsonDoc.toJson());
                file.close();

                qDebug() << "Object deleted successfully.";
                return true ;
            } else {
                qDebug() << "Error: Unable to open the file for writing.";
                // return false;
            }
        } else {
            qDebug() << "Error: Object key not found.";
            // return fa;
        }
    } else {
        qDebug() << "Error: Invalid JSON document. Expected an object.";
        // return ;
    }
    return false;
};
