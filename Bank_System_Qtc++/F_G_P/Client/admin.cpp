<<<<<<< HEAD

=======
>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb
#include "admin.h"
#include <iostream>
#include <QTextStream>

QTextStream Qin(stdin);
QTextStream Qout(stdout);

Admin::Admin()
{
<<<<<<< HEAD
    _type="admin";
    outStream.setDevice(&socket);
    outStream.setVersion(QDataStream::Qt_6_4);
    inStream.setDevice(&socket);
    inStream.setVersion(QDataStream::Qt_6_4); 
=======
    outStream.setDevice(&socket);
    outStream.setVersion(QDataStream::Qt_6_4);
    inStream.setDevice(&socket);
    inStream.setVersion(QDataStream::Qt_6_4);
    _type="admin";
>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb
    connect(&socket,&QTcpSocket::connected,this,&Admin::connected);
    connect(&socket,&QTcpSocket::disconnected,this,&Admin::disconnected);
    connect(&socket,&QTcpSocket::stateChanged,this,&Admin::stateChanged);
    connect(&socket,&QTcpSocket::readyRead,this,&Admin::readyRead);
    connect(&socket,&QTcpSocket::errorOccurred,this,&Admin::error);
}



void Admin::AdminStart(bool)
{
<<<<<<< HEAD
    system("cls");
=======
>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb
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
<<<<<<< HEAD
              request="Get Acc No";
=======
              request="Get Account Number";
>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb
              sendrequesttoserver(request);
              GetAccNo();

              break;

          case 2:
<<<<<<< HEAD
              request="AccountBalance";
=======
              request="View Account Data Base";
>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb
              sendrequesttoserver(request);
              ViewAccount();

              break;

          case 3:
              request="View Transaction";
              sendrequesttoserver(request);
              ViewTransactionHistory();


              break;
          case 4:
<<<<<<< HEAD
              request="ViewBankDatabase";
=======
              request="View All DataBase";
>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb
              sendrequesttoserver(request);
              ViewBankDatabase();

              break;

          case 5:
<<<<<<< HEAD
              request="CreateNewUser";
              sendrequesttoserver(request);
              RecieveUserData();
=======
              request="Create User";
              sendrequesttoserver(request);
              CreateNewUser();
>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb

              break;
          case 6:

<<<<<<< HEAD
              request="UpdateUser";
              sendrequesttoserver(request);
              UpdateUser();

              break;

          case 7:

              request="DeleteUser";
=======
              request="Delete User";
>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb
              sendrequesttoserver(request);
              Deleteuser();


              break;
<<<<<<< HEAD
;
=======
          case 7:

              request="Update User";
              sendrequesttoserver(request);
              UpdateUser();


>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb

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
<<<<<<< HEAD
    QString username,password;
    _request="login";


    outStream<<_request<<_type;
    qInfo()<<"Welcome MR.Admin To Our Bank Managenment System";

    qInfo()<<"Username: ";
    Qin>>username;

    qInfo()<<"Password: ";
    Qin>>password;

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
            a_username = username;
            Qout << "-----------------------------------------" << Qt::endl;


        }
    }
    else
    {
        qInfo() << "User not found, please try again later..";
    }

    return ok;
}

void Admin::ViewAccount()
{   system("cls");
    char chr;
=======
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
>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb
    Qout<<"-------------------------------"<<Qt::endl;
    Qout<<"Please send the account number:"<<Qt::endl;
    QString accountNumber;
    Qin>>accountNumber;

    outStream<<accountNumber;
<<<<<<< HEAD
=======
    socket.waitForBytesWritten();
>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb
    //wait for the respond from the server to view it to the client
    socket.waitForReadyRead();
    if(_respond.toBool() == true)
    {
<<<<<<< HEAD
        qInfo()<<"Your Account Money is :"<<_AccountBalance;
        qInfo()<<"----------------------------------------------";
        qInfo()<<"If you Need To Back To The Admin Menu Press y ";
        Qin>>chr;
        if(chr=='y')
        {
            bool ok=true;
            system("cls");
            AdminStart(ok);
        }


    }
    else
    {
        qInfo()<<"Invalid Account Number";
        qInfo()<<"If you Need To Back To The Admin Menu Press y ";
        Qin>>chr;
        if(chr=='y')
        {
            bool ok=true;
            system("cls");
            AdminStart(ok);
        }


=======
        qInfo()<<"Your Account Money is :"<<_Balane;
    }
    else
    {
        qInfo()<<"Invalid User Name";
>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb

    }

}


void Admin::GetAccNo()
{
<<<<<<< HEAD
    char chr;
    system("cls");
=======
>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb
    QString username;

    Qout << "-----------------------------------------"<<Qt::endl;
    Qout << "Welcome In Get Account Number Mode" << Qt::endl;

    Qout<<"Please Enter the username:"<<Qt::endl;
    Qin>>username;
    outStream<<username;
    //wait for the respond from the server to view it to the client
    socket.waitForReadyRead();
<<<<<<< HEAD
    if(_respond.toBool() == true)
    {
        qInfo()<<"Account Number of User "<<username << " is: " << _accountnumber;
        qInfo()<<"If you Need To Back To The Admin Menu Press y ";
        Qin>>chr;
        if(chr=='y')
        {
            bool ok=true;
            system("cls");
            AdminStart(ok);
        }
=======
    Qout<<"Account Number is :"<<_respond.toString()<<Qt::endl;

    qInfo()<<"View Account Number is:"<<_respond.toBool();
    if(_respond.toBool() == true)
    {
        qInfo()<<"Account Number of User "<<username << " is: " << _accountnumber;
>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb

    }
    else
    {
        qInfo() << "Invalid Username";
<<<<<<< HEAD
        qInfo()<<"If you Need To Back To The Admin Menu Press y ";
        Qin>>chr;
        if(chr=='y')
        {
            bool ok=true;
            system("cls");
            AdminStart(ok);
        }
=======
>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb
    }

}

void Admin::ViewBankDatabase()
{
<<<<<<< HEAD
    char chr;
    system("cls");
    Qout<<"Welcome In Show All Data Base Mode"<<Qt::endl;
=======
    Qout<<"Welcome In Show All Data Base Mode:"<<Qt::endl;
>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb
    socket.waitForReadyRead();
    if(_respond.toBool()==true)
    {
    Qout<<"Your Bank DataBase :"<<_AllDataBase<<Qt::endl;
<<<<<<< HEAD
    qInfo()<<"If you Need To Back To The Admin Menu Press y ";
    Qin>>chr;
    if(chr=='y')
    {
        bool ok=true;
        system("cls");
        AdminStart(ok);
    }
=======
>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb
    }
    else
    {
      Qout<<"Sorry We Can't Send Now To You Our Data Base"<<Qt::endl;
<<<<<<< HEAD
      qInfo()<<"If you Need To Back To The Admin Menu Press y ";
      Qin>>chr;
      if(chr=='y')
      {
          bool ok=true;
          system("cls");
          AdminStart(ok);
      }
    }

}
void Admin::RecieveUserData()
{
    char chr;
    system("cls");
    QString choice,UserName;
    QVariantMap Data_Map;
    QString Age=0,Balance=0,password=0;
    qInfo()<<"Please Enter The Role Of New Member";
    Qin>>choice;
        if(choice.toLower()=="admin")
        {
            qInfo()<<"Please Enter The Name";
            Qin>>UserName;
            outStream<<choice<<UserName;
            socket.waitForReadyRead();

            if(_respond.toBool()== true)
            {
                qInfo()<<"The User Name Already Exists";
            }
            else if(_respond.toBool()== false)
            {
                qInfo()<<"Please Enter The Admin's Password:";
                Qin>>password;
                Data_Map["password"]=password;
                qDebug()<<Data_Map;
                outStream<<Data_Map;
                socket.waitForReadyRead();

            }

            qInfo()<<"If you Need To Back To The Admin Menu Press y ";
            Qin>>chr;
            if(chr=='y')
            {
                bool ok=true;
                system("cls");
                AdminStart(ok);
            }
        }
        else if(choice.toLower()=="user")
        {
            qInfo()<<"Please Enter The Name";
            Qin>>UserName;
            outStream<<choice<<UserName;
            socket.waitForReadyRead();
            if(_respond.toBool()== true)
            {
                qInfo()<<"The User Name Already Exists";
            }
            else
            {
                qInfo()<<"Please Enter The User's Age:";
                Qin>>Age;
                qInfo()<<"Please Enter The User's Balance:";
                Qin>>Balance;
                Data_Map["Age"]=Age;
                Data_Map["Balance"]=Balance;
                outStream<<Data_Map;
                socket.waitForReadyRead();
            }

            qInfo()<<"If you Need To Back To The Admin Menu Press y ";
            Qin>>chr;
            if(chr=='y')
            {
                bool ok=true;
                system("cls");
                AdminStart(ok);
            }
=======
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
>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb
        }
        else
        {
            Qout<<"Your Choice Is Wrong Please Try Again"<<Qt::endl;
<<<<<<< HEAD
            qInfo()<<"If you Need To Back To The Admin Menu Press y ";
            Qin>>chr;
            if(chr=='y')
            {
                bool ok=true;
                system("cls");
                AdminStart(ok);
            }
        }
}




void Admin::Deleteuser()
{   system("cls");
    char chr;
    QString UserName;
    bool _Check=_respond.toBool();
        Qout<<"Please Enter The UserName Which You Need To Delete It:"<<Qt::endl;
        Qin>>UserName;
        outStream<<UserName;
        socket.waitForReadyRead();

        inStream>>_Check;
        if(_Check==true)
        {

            Qout<<"The User Is Deleted Successfully";
            qInfo()<<"If you Need To Back To The Admin Menu Press y ";
            Qin>>chr;
            if(chr=='y')
            {
                qInfo()<<"If you Need To Back To The Admin Menu Press y ";
                Qin>>chr;
                if(chr=='y')
                {
                    bool ok=true;
                    system("cls");
                    AdminStart(ok);
                }
            }
=======
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
>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb
        }
        else
        {
            Qout<<"The Account Number Which You Enterd Is False Please Try Again";
<<<<<<< HEAD


            qInfo()<<"If you Need To Back To The Admin Menu Press y ";
            Qin>>chr;
            if(chr=='y')
            {
                bool ok=true;
                system("cls");
                AdminStart(ok);
            }
        }
=======
            _cntr=0;
        }
    }while(_cntr==0);
>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb

}

void Admin::UpdateUser()
{
<<<<<<< HEAD
    char chr;
  QString username,choice,value;
  qInfo()<<"---------------------------------------------------";
  qInfo()<<"Please Enter The User Name Which You Want To Update";
  Qin>>username;
  outStream<<username;
  socket.waitForReadyRead();
  if(_respond.toBool()==true)
  {
       qInfo()<<"Please Enter The Field Which You Want To Update ";
       Qin>>choice;
       if(choice=="password")
       {
          qInfo()<<"Please Enter The New Password";
          Qin >> value;
          outStream<<choice<<value;
          socket.waitForReadyRead();
          qInfo()<<"If you Need To Back To The Admin Menu Press y ";
          Qin>>chr;
          if(chr=='y')
          {
              bool ok=true;
              system("cls");
              AdminStart(ok);
          }
       }

       else if(choice=="Age")
       {
           qInfo()<<"Please Enter The New Age";
           Qin >> value;
           outStream<<choice<<value;
           socket.waitForReadyRead();
           qInfo()<<"If you Need To Back To The Admin Menu Press y ";
           Qin>>chr;
           if(chr=='y')
           {
               bool ok=true;
               system("cls");
               AdminStart(ok);
           }
       }

       else if(choice=="Balance")
       {
           qInfo()<<"Please Enter The New Balance";
           Qin >> value;
           outStream<<choice<<value;
           socket.waitForReadyRead();
           qInfo()<<"If you Need To Back To The Admin Menu Press y ";
           Qin>>chr;
           if(chr=='y')
           {
               bool ok=true;
               system("cls");
               AdminStart(ok);
           }
       }
     }
    else
    {  qInfo()<<"If you Need To Back To The Admin Menu Press y ";
       Qin>>chr;
       if(chr=='y')
        {
                bool ok=true;
                system("cls");
                AdminStart(ok);
        }
    }
    }





void Admin::ViewTransactionHistory()
{
    char chr;
    QString _cntr,username;
    QDataStream outStream(&socket);
    outStream.setVersion(QDataStream::Qt_6_4);

    qInfo()<<"-----------------------------------------";
    qInfo()<<"Welcome In View Transaction History Mode ";
    qInfo()<<"Please Enter The User Name:";
    Qin>>username;

    Qout<<"Please Enter The Count Of The Transction Which You Want:"<<Qt::endl;
    Qin>>_cntr;
    outStream<<username<<_cntr;
    socket.waitForReadyRead();
    Qout <<"Your Transaction History Is Equal"<< _respond.toString()<<Qt::endl;

    qInfo()<<"If you Need To Back To The Admin Menu Press y ";
    Qin>>chr;
    if(chr=='y')
    {
        bool ok=true;
        system("cls");
        AdminStart(ok);
=======

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
>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb
    }
}


void Admin::sendrequesttoserver(QString request)
{
<<<<<<< HEAD
    system("cls");
    QDataStream outStream(&socket);
    outStream.setVersion(QDataStream::Qt_6_4);
    _request=request;
    outStream<<_request<<_type;
=======
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
>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb

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
<<<<<<< HEAD
 inStream.setVersion(QDataStream::Qt_6_4);

=======
>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb
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

<<<<<<< HEAD
 else if(_request == "View Transaction")
=======
 else if(_request == "ViewTransactionHistory")
>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb
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
<<<<<<< HEAD
     inStream>> respond >> balance;
     _respond.setValue(respond);
     _AccountBalance = balance.toInt();
 }
 else if(_request == "Get Acc No")
=======
     inStream>>respond >> balance;
     _respond.setValue(respond);
     _AccountBalance = balance.toInt();
 }
 else if(_request == "GetAccountNumber")
>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb
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
<<<<<<< HEAD
        //know if the transaction succeed or not from the server and save it in the server respond
=======

     //know if the transaction succeed or not from the server and save it in the server respond
>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb
     inStream>>respond;
     _respond.setValue(respond);

 }
 else if(_request == "CreateNewUser")
 {
     bool respond;
<<<<<<< HEAD
=======

>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb
     inStream>>respond;
     _respond.setValue(respond);

}

}

