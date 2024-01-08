#include "user.h"
#include <iostream>
#include <QDataStream>
#include <QDebug>
#include <QTextStream>
#include <winsock.h>

QTextStream Min(stdin);
QTextStream Mout(stdout);
QDataStream outStream;
QDataStream inStream;

User::User()
{
    _type="user";
    QDataStream outStream(&socket);
    outStream.setDevice(&socket);
    outStream.setVersion(QDataStream::Qt_6_4);
    inStream.setDevice(&socket);
    inStream.setVersion(QDataStream::Qt_6_4);
    connect(&socket,&QTcpSocket::connected,this,&User::connected);
    connect(&socket,&QTcpSocket::disconnected,this,&User::disconnected);
    connect(&socket,&QTcpSocket::stateChanged,this,&User::stateChanged);
    connect(&socket,&QTcpSocket::readyRead,this,&User::readyRead);
    connect(&socket,&QTcpSocket::errorOccurred,this,&User::error);
}

void User::UserStart(bool)
{
    QString input,request;
    qint16 Choice,_flag=0;
    while(_flag==0)
    {
        Mout<<"Welcome Mr.User I Can Help You By Several Services   " <<Qt::endl;
        Mout<<"To Get Acc Number Please Enter No                  (1)" <<Qt::endl;
        Mout<<"To View Acc Balance Please Enter No                (2)" <<Qt::endl;
        Mout<<"To View Transaction History Please Enter No        (3)" <<Qt::endl;
        Mout<<"To View Bank DataBase Please Enter No              (4)" <<Qt::endl;
        Mout<<"To Create New User Please Enter no                 (5)" <<Qt::endl;
        Mout<<"To Update User Data Please Enter no                (6)" <<Qt::endl;
        Mout<<"To Delete User Data Please Enter no                (7)" <<Qt::endl;
        Min >> Choice;

          switch (Choice) {
          case 1:
              request="View Account";
              sendrequesttoserver(request);
              ViewAccount();
              break;

          case 2:
              request="GetAccNo";
              sendrequesttoserver(request);
              GetAccNo();
              break;

          case 3:
              request="View Transaction";
              sendrequesttoserver(request);
              ViewTransactionHistory();
              break;
          case 4:
              request="Make Transaction";
              sendrequesttoserver(request);

              break;

          case 5:
              request="Transfer Account";
              sendrequesttoserver(request);

              break;

          default:
              Mout<<"Your Choice Is Wrong Please Try Again Later\n"<<Qt::endl;

              break;
          }
            Mout<<"If You Need Another Operation Press yes if not pess no "<<Qt::endl;
            Min>>input;

            if(input == "no")
           {
               _flag++;
           }
           else if(input =="yes")
           {
               _flag=0;
           }
}
}


void User::TransferAmount()
{
    QString toaccountnumber;
    QString _amount;
    // create a datastream to send the nedded info to the server to transfer the money.
    QDataStream outStream(&socket);
    outStream.setVersion(QDataStream::Qt_6_4);
    Mout<<"------------------------------------------------------------"<<Qt::endl;
    Mout<<"Welcome in Transfer Amount Mode";
    Mout<<"Please send the account number to which you will transfer:"<<Qt::endl;
    Min>>toaccountnumber;
    Mout<<"Please send the transfer amount:"<<Qt::endl;
    Min>>_amount;

    if(_respond.toBool() == true)
    {
        bool check = false;
        outStream<<_request<<_type<< check;
        Mout << "-----------------------------------------" << Qt::endl;

        Mout << "Please Enter The Transfer amount Which You Want To Transfer It>> " << Qt::endl;
        Min  >>_amount;
        Mout << "-----------------------------------------" << Qt::endl;

        outStream << u_username <<toaccountnumber <<_amount;
        socket.waitForBytesWritten();
        socket.waitForReadyRead();
        if(_respond.toBool() == true)
        {
            Mout<<"The Transfer Money is :"<<_respond.toBool()<<Qt::endl;

        }
        else
        {
            Mout << "Transfer Amount is not valid please try again"<<Qt::endl;
        }
    }
    else
    {
        Mout << "Wrong  From User name try again"<<Qt::endl;
        TransferAmount();

    }
}

void User::MakeTransaction()
{
    QString _amount, _type,_transaction;
    Mout << "----------------------------------------------"<<Qt::endl;
    Mout << "Welcome In Transaction Mode" << Qt::endl;
    Mout << "Which Type Of Transaction You Want Decrease Or Increase "<<Qt::endl;
    Min >> _type;
    Mout << "-----------------------------------------" << Qt::endl;
    Mout << "Please Enter Your Transaction Amount>> " << Qt::endl;
    Min  >>_amount;
    Mout << "-----------------------------------------" << Qt::endl;


    if(_type.toLower() == "Decrease")
    {
        _transaction = "-" + _amount;
    }
    else if(_type.toLower() == "increase")
    {
        _transaction = _amount;
    }
    else
    {
        Mout << "Invalid option. Please try again" << Qt::endl;
        MakeTransaction();
    }

        Mout << "The transaction To Be Happend Is " << _amount<<Qt::endl;
        outStream <<_transaction << _accountnumber << u_username;

        socket.waitForReadyRead();
        Mout<<"make transaction is :"<<_respond.toBool()<<Qt::endl;
}

void User::ViewAccount()
{
    // create a datastream to send the nedded info to the server to get the the money in the account
    QDataStream outStream(&socket);
    outStream.setVersion(QDataStream::Qt_6_4);
    Mout<<"----------------------------"<<Qt::endl;
    Mout<<"Welcome In View Account Mode"<<Qt::endl;
    outStream<<u_username;

    socket.waitForReadyRead();
    if(_respond==true)
    {
        Mout<<"Your account money is :"<<_AccountBalance<<Qt::endl;
        Mout<<"----------------------------------------"<<Qt::endl;
    }
    else
    {
        Mout<<"We Can't View Now Your Account Balance"<<Qt::endl;
        Mout<<"--------------------------------------"<<Qt::endl;
    }

}

void User::GetAccNo()
{
    Mout<<"-------------------------------"<<Qt::endl;
    Mout<<"Welcome In Get Acc Mode"<<Qt::endl;
    outStream<<u_username;
    socket.waitForReadyRead();

    if(_respond.toBool()==true)
    {
        Mout<<"Your account number is:"<<_accountnumber<<Qt::endl;
    }
    else
    {
        Mout<<"We Are Sorry We Can't Give Your Account Number Now"<<Qt::endl;
    }

}

void User::ViewTransactionHistory()
{
    quint32 _cntr;
    QDataStream outStream(&socket);
    outStream.setVersion(QDataStream::Qt_6_4);

    Mout<<"-----------------------------------------"<<Qt::endl;
    Mout<<"Welcome In View Transaction History Mode "<<Qt::endl;

    Mout<<"Please Enter The Count Of The Transction Which You Want:"<<Qt::endl;
    Min>>_cntr;

    outStream<<u_username<<_cntr;
    socket.waitForBytesWritten();
    socket.waitForReadyRead();
    Mout <<"Your Transaction HistoryIs Equal"<< _respond.toString()<<Qt::endl;
}

void User::sendrequesttoserver(QString request)
{
    QDataStream outStream(&socket);
    outStream.setVersion(QDataStream::Qt_6_4);
    _request=request;
    outStream<<_request<<_type;

    if(request=="Transfer Account")
    {
        //call the method Transfer Account to handle this request
        TransferAmount();
    }
    else if(request=="View Account")
    {
        //call the method view Account to handle this request
        ViewAccount();
    }
    else if(request=="Make Transaction")
    {
        MakeTransaction();
    }
    else if(request=="Get Acc No")
    {
        GetAccNo();
    }
    else if(request=="View Transaction History")
    {
        ViewTransactionHistory();
    }
    else
    {
        qInfo() << "The request message is not defined";
    }

}

bool User::Login()
{
    QString username,password;
    _request="login";


    outStream<<_request<<_type;
    qDebug()<<"Welcome MR.USER TO Our Bank Managenment System";

    qDebug()<<"Username: ";
    Min>>username;

    qDebug()<<"Password: ";
    Min>>password;

    bool ok =false;

    quint8 count =0;
    while(count<3)
    {
        count++;
        if(!username.isEmpty()&&!password.isEmpty())
        {
            ok=true;
            break;
        }
    }
    if (ok)
    {
        //send the data to the server to handle that
        outStream<<username<<password;
        socket.waitForReadyRead();
        qInfo()<<"login is :"<<_respond.toBool();
        ok = _respond.toBool();
        if(_respond.toBool() == true)
        {
            u_username = username;
            Mout << "-----------------------------------------" << Qt::endl;
            sendrequesttoserver("GetAccountNumber");
        }
    }
    else
    {
        qInfo() << "User not found, please try again later..";
    }

    return ok;
}



void User::connectToHost(QString host, quint16 port)
{
    if(socket.isOpen()) disconnect();
    //qInfo()<<"connecting to host"<<host<<"on port:"<<port;
    socket.connectToHost(host,port);
}

void User::disconnect()
{
    socket.close();
    socket.disconnectFromHost();
    socket.waitForDisconnected();
}

void User::connected()
{
    QTextStream input(stdin, QIODevice::ReadOnly);
    QString userInput = input.readLine().trimmed();
    socket.write(userInput.toUtf8());
}

void User::disconnected()
{
    Mout<<"Thank you!...system is closing";
    Mout<<"Disconnected";
}

void User::error(QAbstractSocket::SocketError socketerror)
{
    Mout<<"Error:"<<socketerror<<socket.errorString();
}

void User::stateChanged(QAbstractSocket::SocketState socketstate)
{
    QMetaEnum metaenum = QMetaEnum::fromType<QAbstractSocket::SocketState>();
    QString str= metaenum.valueToKey(socketstate);
}

void User::readyRead()
{
    QDataStream inStream(&socket);
    inStream.setVersion(QDataStream::Qt_6_4);

    if (_request=="View Account")
    {
        QString respond;
        //take the money in the account from the server and save it in the server respond
        inStream>>respond;
        _respond.setValue(respond);
    }
    else if(_request=="Transfer Account"||_request=="Make Transaction")
    {
        bool respond;
        //know if the transaction succeed or not from the server and save it in the server respond
        inStream>>respond;
        _respond.setValue(respond);
    }
    else if(_request=="Get Acc No")
    {
        QString AccNo;
        inStream>>AccNo;
        _respond.setValue(AccNo);
    }
    else if(_request=="View Transaction History")
    {
        QString History;
        inStream>>History;
        _respond.setValue(History);
    }
    else if(_request=="login")
    {
        bool respond;
        //know if the transaction succeed or not from the server and save it in the server respond
        inStream>>respond;
        _respond.setValue(respond);
    }
    else if(_request == "AccountBalance")
    {
        bool respond;
        QString balance ;
        //know if the transaction succeed or not from the server and save it in the server respond
        inStream>>respond >> balance;
        _respond.setValue(respond);
        _AccountBalance = balance.toInt();
    }
}


