#include "admin.h"
#include <iostream>
#include <QTextStream>

QTextStream Qin(stdin);
QTextStream Qout(stdout);

Admin::Admin()
{
    outStream.setDevice(&socket);
    outStream.setVersion(QDataStream::Qt_6_4);
    inStream.setDevice(&socket);
    inStream.setVersion(QDataStream::Qt_6_4);
    _type="admin";
    connect(&socket,&QTcpSocket::connected,this,&Admin::connected);
    connect(&socket,&QTcpSocket::disconnected,this,&Admin::disconnected);
    connect(&socket,&QTcpSocket::stateChanged,this,&Admin::stateChanged);
    connect(&socket,&QTcpSocket::readyRead,this,&Admin::readyRead);
    connect(&socket,&QTcpSocket::errorOccurred,this,&Admin::error);
}



void Admin::AdminStart(bool)
{
    QString input,request  ;
    qint16 Choice,_flag=0;
    while(_flag==0)
    {
        Qout<<"------------------------------------------------------" <<Qt::endl;
        Qout<<"Welcome Mr.Admin I Can Help You By Several Services   " <<Qt::endl;
        Qout<<"To Get Acc Number Please Enter No                  (1)" <<Qt::endl;
        Qout<<"To View Acc Balance Please Enter No                (2)" <<Qt::endl;
        Qout<<"To View Transaction History Please Enter No        (3)" <<Qt::endl;
        Qout<<"To View Bank DataBase Please Enter No              (4)" <<Qt::endl;
        Qout<<"To Create New User Please Enter no                 (5)" <<Qt::endl;
        Qout<<"To Update User Data Please Enter no                (6)" <<Qt::endl;
        Qout<<"To Delete User Data Please Enter no                (7)" <<Qt::endl;
        Qout<<"------------------------------------------------------" <<Qt::endl;
        Qin >> Choice;


          switch (Choice) {
          case 1:
              request="Get Account Number";
              sendrequesttoserver(request);
              GetAccNo();

              break;

          case 2:
              request="View Account Data Base";
              sendrequesttoserver(request);
              ViewAccount();

              break;

          case 3:
              request="View Transaction";
              sendrequesttoserver(request);
              ViewTransactionHistory();


              break;
          case 4:
              request="View All DataBase";
              sendrequesttoserver(request);
              ViewBankDatabase();

              break;

          case 5:
              request="Create User";
              sendrequesttoserver(request);
              CreateNewUser();

              break;
          case 6:

              request="Delete User";
              sendrequesttoserver(request);
              Deleteuser();


              break;
          case 7:

              request="Update User";
              sendrequesttoserver(request);
              UpdateUser();



              break;

          default:
              Qout<<"Your Choice Is Wrong Please Try Again Later\n"<<Qt::endl;

              break;
          }
            Qout<<"If You Need Another Operation Press yes if not pess no "<<Qt::endl;
            Qin>>input;

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


bool Admin::Login()
{
    QString _AdminNameLoc,_PassWordLoc;
    quint16 _cntr=0;
    bool ok =true;

    _request="login";
    outStream<<_request<<_type;

    qDebug()<<"Welcome MR.USER TO Our Bank Managenment System";
    Qout<<"----------------------------"<<Qt::endl;
    Qout<<"Hello Admin "<<Qt::endl;

    Qout<<"Please Enter Your User Name:"<<Qt::endl;
    Qin >>_AdminNameLoc;


    Qout<<"Please Enter Your Password:"<<Qt::endl;
    Qin >>_PassWordLoc;
    Qout<<"---------------------------"<<Qt::endl;

    _Adminname = _AdminNameLoc;
    outStream<<_AdminNameLoc<<_PassWordLoc;
    socket.waitForReadyRead();

    while(_cntr<3)
    {
       _cntr++;
       if(!_AdminNameLoc.isEmpty()&&!_PassWordLoc.isEmpty())
       {
           ok=true;
       }

       if (ok)
       {
           //send the data to the server to handle that
           outStream<<_AdminNameLoc<<_PassWordLoc;
           socket.waitForReadyRead();
           qInfo()<<"login is :"<<_respond.toBool();
           ok = _respond.toBool();
       }
       else
       {
           Qout << "User not found, please try again later.."<<Qt::endl;
       }
}
       return ok;

}
void Admin::ViewAccount()
{
    Qout<<"-------------------------------"<<Qt::endl;
    Qout<<"Please send the account number:"<<Qt::endl;
    QString accountNumber;
    Qin>>accountNumber;

    outStream<<accountNumber;
    socket.waitForBytesWritten();
    //wait for the respond from the server to view it to the client
    socket.waitForReadyRead();
    if(_respond.toBool() == true)
    {
        qInfo()<<"Your Account Money is :"<<_Balane;
    }
    else
    {
        qInfo()<<"Invalid User Name";

    }

}


void Admin::GetAccNo()
{
    QString username;

    Qout << "-----------------------------------------"<<Qt::endl;
    Qout << "Welcome In Get Account Number Mode" << Qt::endl;

    Qout<<"Please Enter the username:"<<Qt::endl;
    Qin>>username;
    outStream<<username;
    //wait for the respond from the server to view it to the client
    socket.waitForReadyRead();
    Qout<<"Account Number is :"<<_respond.toString()<<Qt::endl;

    qInfo()<<"View Account Number is:"<<_respond.toBool();
    if(_respond.toBool() == true)
    {
        qInfo()<<"Account Number of User "<<username << " is: " << _accountnumber;

    }
    else
    {
        qInfo() << "Invalid Username";
    }

}

void Admin::ViewBankDatabase()
{
    Qout<<"Welcome In Show All Data Base Mode:"<<Qt::endl;
    socket.waitForReadyRead();
    if(_respond.toBool()==true)
    {
    Qout<<"Your Bank DataBase :"<<_AllDataBase<<Qt::endl;
    }
    else
    {
      Qout<<"Sorry We Can't Send Now To You Our Data Base"<<Qt::endl;
    }

}
void Admin::RecieveUserData(QString choice,QString UserName)
{
    QVariantMap Data_Map;
    qint16 _Cntr=0;
    QString Age=0,Balance=0;
    while(_Cntr==0)
    {
        if(choice=="admin")
        {
            Qout<<"Please Enter The User's Age:"<<Qt::endl;
            Qin>>Age;
            Data_Map["Age"]=Age;
            Data_Map["Username"]=UserName;
            socket.waitForReadyRead();
            outStream<<Data_Map;
            _Cntr++;
        }
        else if(choice=="user")
        {
            Qout<<"Please Enter The User's Age:"    <<Qt::endl;
            Qin>>Age;
            Qout<<"Please Enter The User's Balnace:"<<Qt::endl;
            Qin>>Balance;

            Data_Map["Username"]=UserName;
            Data_Map["Age"]=Age;
            Data_Map["Balance"]=Balance;

            socket.waitForBytesWritten();
            socket.waitForReadyRead();

            outStream<<Data_Map;
            _Cntr++;
        }
        else
        {
            Qout<<"Your Choice Is Wrong Please Try Again"<<Qt::endl;
        }
    }

}
void Admin::CreateNewUser()
{
    qint16 _Cntr=0;
    QString UserType,Username;
    Qout<< "Please Enter The New Member Name"<<Qt::endl;
    Qin >>Username;
    Qout<<"Please Enter The New Member Type Admin Or User if The New Member Is Admin Enter admin And If User Press user "<<Qt::endl;
    Qin >>UserType;
    outStream<<Username<<UserType;

    bool _Check=_respond.toBool();
    while(_Cntr!=0)
    {
        if (_Check==true)
        {
            RecieveUserData(UserType,Username);
            _Cntr=0;
        }
        else if(_Check==false)
        {
            Qout<<"The Named Which You Entered Is Already Exist"<<Qt::endl;
            _Cntr++;
        }
    }
}

void Admin::Deleteuser()
{
    QString AccountNumber;
    quint16 _cntr=0;
    bool _Check=_respond.toBool();
    do
    {
        Qout<<"Please Enter The AccountNumber Which You Need To Delete It:"<<Qt::endl;
        Qin>>AccountNumber;
        outStream<<AccountNumber;
        socket.waitForBytesWritten();
        socket.waitForReadyRead();

        if(_Check==true)
        {
            Qout<<"The User Is Deleted Successfully";
            _cntr++;
        }
        else
        {
            Qout<<"The Account Number Which You Enterd Is False Please Try Again";
            _cntr=0;
        }
    }while(_cntr==0);

}

void Admin::UpdateUser()
{

}

void Admin::ViewTransactionHistory()
{
    QString _username,_cntr;
    Qout << "-----------------------------------------"<<Qt::endl;
    Qout << "Welcome In View Transaction History Mode" << Qt::endl;
    Qout << "Please Enter Your username:" << Qt::endl;
    Qin >> _username;
    Qout << "-----------------------------------------" << Qt::endl;
    Qout << "Please Enter Your Number Of Counts>> " << Qt::endl;
    Qin >> _cntr;
    Qout << "-----------------------------------------" << Qt::endl;

    if(_cntr.toInt() <= 0)
    {
        qInfo() << "Please enter a valid count.";
        ViewTransactionHistory();
    }
    else
    {
        outStream << _username << _cntr;
        socket.waitForBytesWritten();
        //wait for the respond from the server to view it to the client
        socket.waitForReadyRead();
        qDebug().noquote() <<"Your transaction history is :"<<_respond.toString();
    }
}


void Admin::sendrequesttoserver(QString request)
{
    QDataStream outStream(&socket);
    outStream.setVersion(QDataStream::Qt_6_4);
    _request=request;
    outStream<<request<<_type;



    if(request == "Get Account Number")
    {
        //call the method Transfer Account to handle this request
        GetAccNo();
    }
    else if(request == "View Account Data Base")
    {
        //call the method view Account to handle this request
        ViewAccount();
    }
    else if(request=="View All DataBase")
    {
        ViewBankDatabase();
    }
    else if(request == "Create New User")
    {
        CreateNewUser();
    }
    else if(request == "Delete User")
    {
        Deleteuser();
    }
    else if(request == "Update User")
    {
        UpdateUser();
    }
    else if(request == "View Transaction")
    {
        ViewTransactionHistory();
    }

    else
    {
        qInfo() << "The request message is not defined";
    }

}



void Admin::connectToHost(QString host, quint16 port)
{
    if(socket.isOpen()) disconnect();
    //qInfo()<<"connecting to host"<<host<<"on port:"<<port;
    socket.connectToHost(host,port);
}

void Admin::disconnect()
{
    socket.close();
    socket.waitForDisconnected();
}

void Admin::connected()
{
    QTextStream input(stdin, QIODevice::ReadOnly);
    QString userInput = input.readLine().trimmed();
    socket.write(userInput.toUtf8());
}

void Admin::disconnected()
{
    qInfo()<<"Disconnected";
}

void Admin::error(QAbstractSocket::SocketError socketerror)
{
 qInfo()<<"Error:"<<socketerror<<socket.errorString();
}

void Admin::stateChanged(QAbstractSocket::SocketState socketstate)
{
    QMetaEnum metaenum = QMetaEnum::fromType<QAbstractSocket::SocketState>();
    QString str= metaenum.valueToKey(socketstate);
}

void Admin::readyRead()
{
 QDataStream inStream(&socket);
 if(_request=="login")
 {
     bool respond;
     //know if the transaction succeed or not from the server and save it in the server respond
     inStream>>respond;
     _respond.setValue(respond);
 }
 else if ( _request =="ViewAccount")
 {
     QString Account;
     //take the money in the account from the server and save it in the server respond
     inStream>>Account;
     _respond.setValue(Account);
 }
 else if(_request=="DeleteUser")
 {
     bool respond;
     //know if the transaction succeed or not from the server and save it in the server respond
     inStream>>respond;
     _respond.setValue(respond);
 }

 else if(_request == "ViewTransactionHistory")
 {
     QString respond;

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
 else if(_request == "GetAccountNumber")
 {
     bool respond;
     QString account_number;


     //know if the transaction succeed or not from the server and save it in the server respond
     inStream>>respond >> account_number;
     _respond.setValue(respond);
     _accountnumber = account_number;
 }
 else if(_request == "ViewBankDatabase")
 {
     bool respond;
     QString DataBase;
     //know if the transaction succeed or not from the server and save it in the server respond
     inStream>>respond >> DataBase;
     _respond.setValue(respond);
     _AllDataBase = DataBase;
 }
 else if(_request == "UpdateUser")
 {
     bool respond;

     //know if the transaction succeed or not from the server and save it in the server respond
     inStream>>respond;
     _respond.setValue(respond);

 }
 else if(_request == "CreateNewUser")
 {
     bool respond;

     inStream>>respond;
     _respond.setValue(respond);

}

}

