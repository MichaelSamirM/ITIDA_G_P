#include <QCoreApplication>
#include <QDebug>
#include <iostream>
#include <windows.h>
#include <QTextStream>
#include "user.h"
#include "admin.h"


QTextStream input(stdin);
QTextStream output(stdout);

void clearScreen()
{
    system("cls");

}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString mode;
<<<<<<< HEAD

    output<<"Welcome To IMT Bank Managenment System"<<Qt::endl;
    output<<"Enter Which role you Are Admin Or User"<<Qt::endl;
=======
    output<<"-------------------------------------------"<<Qt::endl;
    output<<"Welcome To IMT_ITIDA Bank Managenent System"<<Qt::endl;
    output<<"Please Choose Which Role you Will be in Our System"<<Qt::endl;
>>>>>>> eae4a420cfac246618c7e417b85bb208e83ae4fb
    input>>mode;
    //connectToHost(QHostAddress::LocalHost, 1234);
    clearScreen();

     if(mode.toUpper()=="USER")
     {
         User user;
         user.connectToHost("127.0.0.1", 1234);
         bool _Status= user.Login();
               while(!_Status)
             {
                 _Status =user.Login();

                 if(!_Status)
                 qInfo("Username or Password is wrong!!\nPlease Try Again");
             }
               while(_Status)
               {
                   user.UserStart(_Status);
               }
     }
     else if(mode.toUpper()=="ADMIN")
     {
         Admin admin;
         admin.connectToHost("127.0.0.1", 1234);
         bool _Status= admin.Login();
               while(!_Status)
             {
                 _Status =admin.Login();

                 if(!_Status)
                 qInfo("Username or Password is wrong!!\nPlease Try Again");
             }
               while(_Status)
               {
                   admin.AdminStart(_Status);
               }

     }

     else if(mode.toUpper()=="EXIT")
     {
         qInfo()<<"Thank you!....Sysyem is closing..";
     }
     else
     {
         qInfo()<<"Sorry you're entering invalid input";
     }

     output<<"BYE...BYE"<<Qt::endl;
     exit(122);
     return a.exec();
}

