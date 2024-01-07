#include <QTcpSocket>
#include "server.h"



<<<<<<< HEAD
Server::Server(JsonFunc *parent)
    : JsonFunc{parent}
{
    connect(&server,&QTcpServer::newConnection,this,&Server::newConnection);

    _path = "D:/ITIDA/Graduation_Project/F_G_P/F_G_P/Data_Base/";
    _historyfile   = "Trans_History.json";
    _usersfile     = "User_d_b.json";
    _adminsfile    = "Admin_d_b.json";
=======
Server::Server(JsonHandler *parent)
    : JsonHandler{*parent}
{
    connect(&server,&QTcpServer::newConnection,this,&Server::newConnection);

    m_path = "D:/ITIDA/Graduation_Project/Graduation/Data_Base/";
    m_historyfile   = "Trans_History.json";
    m_usersfile     = "User_d_b .json";
    m_adminsfile    = "Admin_d_b.json";
>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb


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
<<<<<<< HEAD
   // if (socket) {
        qInfo() << "new connection";
        connect(socket, &QTcpSocket::disconnected, this, &Server::disconnected);
        connect(socket, &QTcpSocket::readyRead, this, &Server::OnreadyRead);
        qInfo() << "connected to" << socket;
    //}
=======
    connect(socket,&QTcpSocket::disconnected,this,&Server::disconnected);
    connect(socket,&QTcpSocket::readyRead,this,&Server::OnreadyRead);
    qInfo()<<"connected to"<<socket;
>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb
}

void Server::disconnected()
{
    QTcpSocket* socket=qobject_cast<QTcpSocket*>(sender());
    qInfo()<<"Disconnected"<<socket;
}



void Server::OnreadyRead()
{
<<<<<<< HEAD
      //create pointer to the socket connected to the object send the request
=======

    //create pointer to the socket connected to the object send the request
>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb
    QTcpSocket* socket=qobject_cast<QTcpSocket*>(sender());
    //create an in datasream to take the needed data from the client
    QDataStream inStream(socket);
    inStream.setVersion(QDataStream::Qt_6_4);
<<<<<<< HEAD

    inStream>>_request>>_type;

    HandlClienterequest(_request,_type);
=======
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
>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb
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
<<<<<<< HEAD
        if(_request=="Transfer Amount")
        {
            bool ok;
            QString file = _path + _usersfile;

            QString fromUsername, toaccountnumber,  transferamount,fromaccountnumber,check;



                ok =true;

                inStream>>ok>> fromUsername >> toaccountnumber ;
                printObjectFields(file, fromUsername, "Account Number", fromaccountnumber);
                qDebug()<<fromaccountnumber;
                ok = JsonFunc::checkObject(file, toaccountnumber);
                outStream<<ok;
                qDebug() << "Received from client:" << fromUsername << " " << toaccountnumber;

            if(ok == false)
            {
                socket->waitForBytesWritten();
                inStream >> fromUsername >>  toaccountnumber >> transferamount;
=======
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
>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb
                //send data to the method transfer acount to check and process on them using json methods
                qint32 Transferamount = transferamount.toInt(&ok);
                if(ok == true)
                {
                    if(Transferamount >=0)
                    {
<<<<<<< HEAD
                        ok = JsonFunc::TransferAmount(file, fromaccountnumber, toaccountnumber, transferamount);
=======
                        ok = JsonHandler::TransferAmount(file, fromUsername, toUsername, transferamount);
>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb
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
<<<<<<< HEAD
        else if(_request=="View Account")
        {
            bool ok;
            QString username,respond;
            inStream >> username;
            QString file = _path + _usersfile;
            ok =printObjectFields(file, username, "Balance", respond);
            outStream <<ok<<respond;
            //sending respond to the server using the socket
            qDebug()<<respond;
=======
        else if(_request=="ViewAccount")
        {
            QString username;
            inStream >> username;
            QString file = m_path + m_usersfile;
            QString respond =  JsonHandler::ViewUserField(file, username);

            //sending respond to the server using the socket
            outStream<<respond;
>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb
        }
        //Done
        else if(_request=="login")
        {
            bool ok = true;
            QString username,password;
            inStream >> username >> password ;
<<<<<<< HEAD
            QString file = _path + _usersfile;
            qInfo()<<file;
            ok = authenticateUser(file, username, password);
=======
            QString file = m_path + m_usersfile;
            ok = JsonHandler::authenticateUser(file, username, password);
>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb
            qDebug() << "authenticaed" << ok;
            qDebug() << "Received from client:" << username<<" "<<password ;
            //sending respond to the server using the socket
            outStream<<ok;

        }
        //Done
<<<<<<< HEAD
        else if(_request=="Get Acc No")
=======
        else if(_request=="GetAccountNumber")
>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb
        {
            bool ok;
            QString username, respond;
            inStream >> username ;
<<<<<<< HEAD
            QString file = _path + _usersfile;
            ok =printObjectFields(file, username, "Account Number", respond);
            outStream <<ok<<respond;
=======
            QString file = m_path + m_usersfile;
            // ok =printObjectFields(file, username);
            ok = JsonHandler::printObjectFields(file, username, "Account Number", respond);
            outStream << ok << respond;
>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb

        }
        //Done
        else if(_request=="AccountBalance")
        {
<<<<<<< HEAD
           bool ok;
           QString username, respond;
           inStream >> username ;
           QString file = _path + _usersfile;
           // ok =printObjectFields(file, username);
           ok =JsonFunc::printObjectFields(file, username, "Balance", respond);
           outStream << ok << respond;

        }
        //hnkmlha
        else if(_request == "Make Transaction")
        {
            QString amount;
            QString username;
            inStream >> amount>> username;
            qDebug()<<amount<<username;
            QString file = _path + _usersfile;
            QString fileName = _path + _historyfile;
            bool ok = JsonFunc::UpdateBalance(fileName, file,username, amount);
=======
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
>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb
            outStream<<ok;

        }
        //lesa
<<<<<<< HEAD
        else if(_request == "View Transaction History")
=======
        else if(_request == "TransactionHistory")
>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb
        {
            QString username;
            QString count;
            inStream >> username >> count ;
<<<<<<< HEAD
            qDebug()<<username<<count;
            quint16 recieved_count = count.toInt();
            qDebug() << "username" << username << "recieved_count" << recieved_count ;
            QString fileName = _path + _historyfile;
            QString respond = JsonFunc::ViewHistory(fileName, username, recieved_count);
=======
            quint16 recieved_count = count.toInt();
            qDebug() << "username" << username << "recieved_count" << recieved_count ;

            QString fileName = m_path + m_historyfile;

            QString respond = JsonHandler::ViewHistory(fileName, username, recieved_count);
>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb
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
<<<<<<< HEAD
            QString file = _path + _adminsfile;
            ok = authenticateUser(file, username, password);
            qDebug() << "authenticated" << ok;
            qDebug() << "Received from client:" << username<<" "<<password ;
            //sending respond to the server using the socket
=======
            qDebug() << "Received from client:" << username<<" "<<password ;
            QString file = m_path + m_adminsfile;
            ok = JsonHandler::authenticateUser(file, username, password);
            qDebug() << "authenticated" << ok;
            //qDebug() << "Received from client:" << username<<" "<<password ;
            //sending respond to the server using the socket

>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb
            outStream<<ok;

        }
        else if(_request=="AccountBalance")
        {
            bool ok;
            QString username, respond;
            inStream >> username ;
<<<<<<< HEAD
            QString file = _path + _usersfile;
            ok =printObjectFields(file, username, "Balance", respond);
            qInfo()<<respond;
            outStream << ok << respond;

        }
        else if(_request=="Get Acc No")
        {
            bool ok=true;
            QString username,respond;
            inStream >> username ;
            QString file = _path + _usersfile;
            ok = printObjectFields(file, username, "Account Number", respond);
            qDebug()<<ok;
            outStream << ok<<respond;
=======
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
>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb

        }
        else if(_request == "ViewBankDatabase")
        {
            QString DataBase;
<<<<<<< HEAD
            QString file = _path + _usersfile;
            bool ok = JsonFunc::PrintDataBase(file, DataBase);
=======

            QString file = m_path + m_usersfile;
            bool ok = JsonHandler::PrintDataBase(file, DataBase);
>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb
            outStream << ok << DataBase;
        }
        else if(_request == "UpdateUser")
        {
<<<<<<< HEAD
            QString username,choice,newvalue;
            QString file=_path+_usersfile;
            inStream>>username;
            bool ok=JsonFunc::checkObject(file,username);
            outStream<<ok;
            socket->waitForReadyRead();
            if (ok==true)
            {
                inStream>>choice>>newvalue;
                qInfo()<<"hamada;"<<choice<<newvalue;
                if(choice=="password")
                {
                    EditField(file,username,"password",newvalue);

                }

                else if(choice=="Age")
                {
                   EditField(file,username,"Age",newvalue);
                }

                else if(choice=="Balance")
                {
                   EditField(file,username,"Balance",newvalue);

                }
            }
        }

        else if(_request == "DeleteUser")
        {
            bool ok;
            QString file = _path + _usersfile;
            QString FileHistory = _path + _historyfile;
            QString username;
            inStream >> username;
            ok = JsonFunc::deleteObject(file, username);
            if(ok == true)
            {
                bool deleteHistory = JsonFunc::deleteObject(FileHistory, username);
                qDebug() << "history deleted" << deleteHistory;

            }
            outStream << ok;
=======
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
>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb

        }
        else if(_request == "CreateNewUser")
        {
<<<<<<< HEAD
            QString username,role;
            QVariantMap Data_Map;
            inStream>>role>>username;
            qDebug()<<role<<username;
            qDebug()<<role;

            if(role.toLower()=="user")
            {
                QString file = _path + _usersfile;
                bool check=checkObject(file, username);
                qDebug()<<check;

                if(check==true)
                {
                 outStream<< check;
                }
                else if(check==false)
                {
                    outStream<<check;
                    socket->waitForReadyRead();
                    inStream>>Data_Map;
                    Data_Map["password"].toString();
                    QString NewObjectName = username;
                    quint32 accountnumber = generateUniqueNumber(username);
                    QString Accountnumber = QString::number(accountnumber);
                    Data_Map["Account Number"]= Accountnumber;
                    bool ok = JsonFunc::AddNewObject(file, Data_Map, NewObjectName);
                    if(ok==true)
                    {
                        qInfo()<<"The New User Added Successfully";
                    }
                    else
                    {
                        qInfo()<<"We Are Sorry ";
                    }
                }
            }
            else if(role.toLower()=="admin")
            {
                QString file = _path + _adminsfile;
                bool check=checkObject(file, username);
                qDebug()<<check;

                if(check==true)
                {
                 outStream<< check  ;
                }
                else
                {
                    outStream<<check;
                    socket->waitForReadyRead();
                    inStream>>Data_Map;
                    Data_Map["password"].toString();
                    QString NewObjectName = username;
                    bool ok = JsonFunc::AddNewObject(file, Data_Map, NewObjectName);

                    if(ok==true)
                    {
                        qInfo()<<"The New User Added Successfully";
                    }
                    else
                    {
                        qInfo()<<"We Are Soory ";
                    }
                }
            }



        }
        else if(_request == "View Transaction")
=======
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
>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb
        {
            QString username;
            QString count;
            inStream >> username >> count ;
<<<<<<< HEAD
            qDebug()<<username<<count;
            quint16 recieved_count = count.toInt();
            qDebug() << "username" << username << "recieved_count" << recieved_count ;
            QString fileName = _path + _historyfile;
            QString respond = JsonFunc::ViewHistory(fileName, username, recieved_count);
            qDebug() << respond;
            outStream << respond;

=======
            quint16 recieved_count = count.toInt();
            qDebug() << "username" << username << "recieved_count" << recieved_count ;
            QString fileName =m_path+ m_historyfile;

            QString respond = JsonHandler::ViewHistory(fileName, username, recieved_count);
            qDebug() << respond;
            outStream << respond;
>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb
        }
    }
}
