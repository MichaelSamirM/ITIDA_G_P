#include <QTcpSocket>
#include "server.h"



Server::Server(JsonHandler *parent)
    : JsonHandler{*parent}
{
    connect(&server,&QTcpServer::newConnection,this,&Server::newConnection);

    m_path = "D:/ITIDA/Graduation_Project/Graduation/Data_Base/";
    m_historyfile   = "Trans_History.json";
    m_usersfile     = "User_d_b .json";
    m_adminsfile    = "Admin_d_b.json";


}
quint32 Server::generateUniqueNumber(const QString& uniqueString)
{
    return qHash(uniqueString);
}

void Server::start()
{
    if(!server.listen(QHostAddress::Any,1234))
    {
        qWarning()<<server.errorString();
        return;
    }
    qInfo()<<"Server Now Ready To Pair";
}


void Server::quit()
{
    server.close();
}

void Server::newConnection()
{
    QTcpSocket* socket=server.nextPendingConnection();
    connect(socket,&QTcpSocket::disconnected,this,&Server::disconnected);
    connect(socket,&QTcpSocket::readyRead,this,&Server::OnreadyRead);
    qInfo()<<"connected to"<<socket;
}

void Server::disconnected()
{
    QTcpSocket* socket=qobject_cast<QTcpSocket*>(sender());
    qInfo()<<"Disconnected"<<socket;
}



void Server::OnreadyRead()
{

    //create pointer to the socket connected to the object send the request
    QTcpSocket* socket=qobject_cast<QTcpSocket*>(sender());
    //create an in datasream to take the needed data from the client
    QDataStream inStream(socket);
    inStream.setVersion(QDataStream::Qt_6_4);
    //take the request message and the role of our client to be able to handle the request
    QString request,role,requestflag;
    inStream>>requestflag;
    if(requestflag=="CreateUser")
    {
        role="admin";
        request="Create User";
    }
    else if(requestflag=="UpdateUser")
    {
        role="admin";
        request="Update User";
    }
    else if(requestflag=="General")
    {
    inStream>>request>>role;
    qDebug()<<request<<role;
    }
    //call this method to handle the request according to client role
    //setRole(role);
    HandlClienterequest(request,role);
}

void Server::HandlClienterequest(QString _request,QString _type)
{
    QTcpSocket* socket=qobject_cast<QTcpSocket*>(sender());
    //create an in datasream to take the needed data from the client
    QDataStream inStream(socket);
    //create an out datastream to send the respond to the client
    QDataStream outStream(socket);
    inStream.setVersion(QDataStream::Qt_6_4);
    outStream.setVersion(QDataStream::Qt_6_4);
    qDebug()<<"The request "<<_request<<_type;
    //check if oour client is user or admin to handle his request
    if(_type.toUpper()=="USER")
    {
        if(_request=="TransferAmount")
        {
            bool ok;
            QString file = m_path + m_usersfile;

            QString fromUsername, toUsername,  transferamount,check;
            inStream >>ok;


            if(ok ==true)
            {
                inStream >> fromUsername >>toUsername ;
                ok = JsonHandler::checkObject(file, toUsername);
                outStream<<ok;
                qDebug() << "Received from client:" << fromUsername << " " << toUsername;
            }
            else if(ok == false)
            {
                socket->waitForBytesWritten();
                inStream >> fromUsername >> toUsername >> transferamount;
                //send data to the method transfer acount to check and process on them using json methods
                qint32 Transferamount = transferamount.toInt(&ok);
                if(ok == true)
                {
                    if(Transferamount >=0)
                    {
                        ok = JsonHandler::TransferAmount(file, fromUsername, toUsername, transferamount);
                    }
                    else
                    {
                        ok = false;
                        qInfo() << "Transfer amount is too small enter positive number";
                    }
                }
                else
                {
                    ok = false;
                    qInfo() << "Invalid Transfer amount";
                }
            }
            else
            {
                ok = false;
            }
            //sending respond to the server using the socket
            outStream<<ok;
        }
        //Done
        else if(_request=="ViewAccount")
        {
            QString username;
            inStream >> username;
            QString file = m_path + m_usersfile;
            QString respond =  JsonHandler::ViewUserField(file, username);

            //sending respond to the server using the socket
            outStream<<respond;
        }
        //Done
        else if(_request=="login")
        {
            bool ok = true;
            QString username,password;
            inStream >> username >> password ;
            QString file = m_path + m_usersfile;
            ok = JsonHandler::authenticateUser(file, username, password);
            qDebug() << "authenticaed" << ok;
            qDebug() << "Received from client:" << username<<" "<<password ;
            //sending respond to the server using the socket
            outStream<<ok;

        }
        //Done
        else if(_request=="GetAccountNumber")
        {
            bool ok;
            QString username, respond;
            inStream >> username ;
            QString file = m_path + m_usersfile;
            // ok =printObjectFields(file, username);
            ok = JsonHandler::printObjectFields(file, username, "Account Number", respond);
            outStream << ok << respond;

        }
        //Done
        else if(_request=="AccountBalance")
        {
            bool ok;
            QString username, respond;
            inStream >> username ;
            QString file = m_path + m_usersfile;
            // ok =printObjectFields(file, username);
            ok = JsonHandler::printObjectFields(file, username, "Balance", respond);
            outStream << ok << respond;

        }
        //hnkmlha
        else if(_request == "MakeTransaction")
        {
            QString amount;
            QString username;
            QString accountnumber;
            inStream >> amount>> accountnumber>> username;

            QString file = m_path + m_usersfile;
            QString fileName = m_path + m_historyfile;
            bool ok = JsonHandler::updateFile(fileName, file,username,  accountnumber, amount);
            outStream<<ok;

        }
        //lesa
        else if(_request == "TransactionHistory")
        {
            QString username;
            QString count;
            inStream >> username >> count ;
            quint16 recieved_count = count.toInt();
            qDebug() << "username" << username << "recieved_count" << recieved_count ;

            QString fileName = m_path + m_historyfile;

            QString respond = JsonHandler::ViewHistory(fileName, username, recieved_count);
            qDebug() << respond;
            outStream << respond;

        }
    }
    else if(_type.toUpper() == "ADMIN")
    {
        if(_request=="login")
        {
            bool ok = true;
            QString username,password;
            inStream >> username >> password ;
            qDebug() << "Received from client:" << username<<" "<<password ;
            QString file = m_path + m_adminsfile;
            ok = JsonHandler::authenticateUser(file, username, password);
            qDebug() << "authenticated" << ok;
            //qDebug() << "Received from client:" << username<<" "<<password ;
            //sending respond to the server using the socket

            outStream<<ok;

        }
        else if(_request=="AccountBalance")
        {
            bool ok;
            QString username, respond;
            inStream >> username ;
            QString file = m_path + m_usersfile;
            // ok =printObjectFields(file, username);
            ok = JsonHandler::printObjectFields(file, username, "Balance", respond);
            outStream << ok << respond;

        }
        else if(_request=="GetAccountNumber")
        {
            bool ok;
            QString adminname, username, respond;
            inStream >> adminname >> username ;
            QString file = m_path + m_usersfile;
            ok = JsonHandler::printObjectFields(file, username, "Account Number", respond);
            outStream << ok << respond;

        }
        else if(_request == "ViewBankDatabase")
        {
            QString DataBase;

            QString file = m_path + m_usersfile;
            bool ok = JsonHandler::PrintDataBase(file, DataBase);
            outStream << ok << DataBase;
        }
        else if(_request == "UpdateUser")
        {
            QString file = m_path + m_usersfile;
            QString username;
            QString FieldToChange, newValue, repassword,check;
            inStream >>check;

            bool ok =((check.toLower() == "true") ? true : false);
            qDebug() << "ok" << ok ;
            if(ok == true)
            {
                inStream >> username;
                qDebug() << username << " " <<username;
                ok = JsonHandler::checkObject(file, username);
                outStream << ok;
            }
            if(ok == false)
            {
                socket->waitForBytesWritten();
                inStream >> FieldToChange >> username >>newValue;
                qDebug() << "username"  <<username;
                qDebug() << "FieldToChange"  <<FieldToChange;


                if(FieldToChange == "password")
                {
                    inStream  >> repassword;
                    qDebug() << newValue << " " <<repassword;
                    if(newValue == repassword)
                    {
                        ok = JsonHandler::EditField(file, username, FieldToChange, newValue);
                    }
                    else
                    {
                        ok = false;
                    }

                }
                else if(FieldToChange == "Age")
                {
                    qint32 age = newValue.toInt(&ok);
                    if(ok == true)
                    {
                        if(age >= 18 && age <= 90)
                        {
                            qDebug() << newValue ;
                            ok = JsonHandler::EditField(file, username, FieldToChange, newValue);
                        }
                        else
                        {
                            ok = false;

                        }
                    }
                    else
                    {
                        ok = false;
                    }

                }
                else if(FieldToChange == "Balance")
                {
                    qint32 balance = newValue.toInt(&ok);
                    if(ok == true)
                    {
                        if( balance > 0 )
                        {
                            qDebug() << newValue ;
                            ok = JsonHandler::EditField(file, username, FieldToChange, newValue);
                        }
                        else
                        {
                            ok = false;
                        }
                    }
                    else
                    {
                        ok = false;
                    }
                }
                else if(FieldToChange == "fullname")
                {
                    qDebug() << newValue ;
                    QString Newfullname = username + " " + newValue;
                    qDebug() << Newfullname ;

                    ok = JsonHandler::EditField(file, username, FieldToChange, Newfullname);
                }
            }
            outStream << ok;
        }
        else if(_request == "DeleteUser")
        {
            bool ok;
            QString file = m_path + m_usersfile;
            QString FileHistory = m_path + m_historyfile;

            QString username;
            inStream >> username;
            ok = JsonHandler::deleteObject(file, username);
            if(ok == true)
            {
                bool deleteHistory = JsonHandler::deleteObject(FileHistory, username);
                qDebug() << "history deleted" << deleteHistory;

            }
            inStream << ok;

        }
        else if(_request == "CreateNewUser")
        {
            QString file = m_path + m_usersfile;
            QString username, data, password ,repassword, secondName, balance, age,check;
             inStream >> check;

            bool ok =((check.toLower() == "true") ? true : false);
            if(ok == true)
            {
                inStream >> data>> username;
                ok = JsonHandler::checkObject(file, username);
                // outStream << ok;
            }
            else
            {
                inStream >> data;
                if(data == "password")
                {
                    socket->waitForBytesWritten();
                    inStream >> username >> repassword >> password ;
                    qInfo() << "password is " << password << "password again is " << repassword;
                    if(password == repassword)
                    {
                        ok =true;

                    }
                    else
                    {
                        ok =false;
                    }
                    // outStream << ok;
                }
                else if(data == "secondName")
                {
                    socket->waitForBytesWritten();
                    inStream >> username >>secondName;
                    ok =true;
                    // outStream << ok;
                }
                else if(data == "balance")
                {
                    socket->waitForBytesWritten();
                    inStream  >> username >> balance;
                    qint32 Balance = balance.toInt(&ok);
                    if(ok == true)
                    {
                        if(Balance >= 0)
                        {
                            ok =true;
                        }
                        else
                        {
                            ok =false;
                        }
                    }
                    else
                    {
                        ok =false;
                    }
                }
                else if(data == "age")
                {
                    socket->waitForBytesWritten();
                    inStream >>username>>  age;
                    qint32 Age = age.toInt(&ok);
                    qDebug() << "Age = " << Age;
                    if(ok == true)
                    {
                        qDebug() << "Age is " << ok;
                        if(Age >= 18 && Age <= 90 )
                        {
                            ok = true;
                            qDebug() << "Age is " << Age;

                        }
                        else
                        {
                            ok = false;
                        }
                    }
                }
                else if(data == "all")
                {
                    outStream >> username>> password >> secondName >> balance >>age;
                    QVariantMap newObject;
                    QString NewObjectName = username;
                    quint32 accountnumber = generateUniqueNumber(username);

                    QString Accountnumber = QString::number(accountnumber);
                    newObject["Account Number"]= Accountnumber;
                    newObject["Age"] = age;
                    newObject["Balance"] = balance,
                    newObject["fullname"] = username + " "+ secondName;
                    newObject["password"]= password;
                    ok = JsonHandler::AddNewObject(file, newObject, NewObjectName);
                }

            }
            outStream << ok;
        }
        else if(_request == "ViewTransactionHistory")
        {
            QString username;
            QString count;
            inStream >> username >> count ;
            quint16 recieved_count = count.toInt();
            qDebug() << "username" << username << "recieved_count" << recieved_count ;
            QString fileName =m_path+ m_historyfile;

            QString respond = JsonHandler::ViewHistory(fileName, username, recieved_count);
            qDebug() << respond;
            outStream << respond;
        }
    }
}
