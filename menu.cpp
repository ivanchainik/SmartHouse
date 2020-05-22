#include "menu.h"
#include "ui_menu.h"
#include<QPixmap>
/*!
  \file
  \brief Файл, содержащий описание методов класса menu.
  */
#include"registry.h"
#include <QApplication>
#include <string>
#include<fstream>
#include<cstring>
#include "mainmenu.h"
/*!
 * \brief Конструктор класса menu.
 * \param parent-указатель на родительский класс.
 */
menu::menu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);
    QPixmap pix(":/picha/Pichures/LoginScreen.png");
    setWindowTitle("\"Умный дом\" :авторизация");
    ui->label->setPixmap(pix);
    fl=false;
    fl2=false;
}
/*!
 * \brief Деструктор класса menu.
 */
menu::~menu()
{
    delete ui;
}
/*!
 * \brief Метод класса menu, отвечающий за открытие окна регистрации.
 */
void menu::on_pushButton_2_clicked()
{
    Registry *regat=new Registry;
    this->close();
    regat->show();
}
/*!
 * \brief Метод класса menu, отвечающий за авторизацию и переход к главному меню.
 */
void menu::on_pushButton_clicked()
{
    std::string login = ui->lineEdit->text().toStdString();
    std::ifstream file;
    int k;
    char *str;
    double m;

    file.open("logins.dat",std::ios_base::binary);
    if(!file.is_open())
    {
        ui->warning->setStyleSheet("QLabel {background-color: rgb(204, 0, 0);color: rgb(238, 238, 236);}");
        ui->warning->setText(" Данного пользователя не существует.");
    }
    else
    {
       while(1)
       {
           file.read((char*)&k,sizeof(int));
           str=new char[k+1];
           file.read((char*)str,sizeof(char)*k);
           strcat(str,"\0");
           if(file.eof())
           {
               delete []str;
               ui->warning->setStyleSheet("QLabel {background-color: rgb(204, 0, 0);color: rgb(238, 238, 236);}");
               ui->warning->setText(" Данного пользователя не существует.");
               break;
           }
           else if(!strcmp(login.c_str(),str))
           {
               delete []str;
               file.read((char*)&k,sizeof(int));
               str=new char[k+1];
               file.read((char*)str,sizeof(char)*k);
               strcpy(str+k,"\0");
               std::string pass =ui->lineEdit_2->text().toStdString();
               if(!strcmp(pass.c_str(),str))
               {
                   bool adm;
                   double m;

                   delete[]str;
                   file.read((char*)&k,sizeof(int));
                   file.read((char*)&m,sizeof(double));
                   adm=(k==1)? true:false ;
                   mainmenu * w=new mainmenu(login,pass,adm,m,0);
                   delete this;
                   w->show();
                   break;
               }
               else
               {
                   delete[] str;
                   ui->warning->setStyleSheet("QLabel {background-color: rgb(204, 0, 0);color: rgb(238, 238, 236);}");
                   ui->warning->setText("\t      Неверный пароль.");
                   file.close();
                   break;
               }
           }
           delete []str;
           file.read((char*)&k,sizeof(int));
           str=new char[k];
           file.read((char*)str,sizeof(char)*k);
           delete []str;
           file.read((char*)&k,sizeof(int));
           file.read((char*)&m,sizeof(double));
       }
    }
}
/*!
 * \brief Метод класса menu, очищающий поле ввода логина.
 */
void menu::on_lineEdit_selectionChanged()
{
    if(fl==false)
    {
        ui->lineEdit->clear();
    }
}
/*!
 * \brief Метод класса menu, очищающий поле ввода пароля.
 */
void menu::on_lineEdit_2_selectionChanged()
{
    if(fl2==false)
    {
        ui->lineEdit_2->clear();
        ui->lineEdit_2->setEchoMode(QLineEdit::EchoMode::Password);
    }
}
