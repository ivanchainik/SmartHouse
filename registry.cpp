/*!
  \file
  \brief Файл, содержащий описание методов класса Registry.
  */
#include "registry.h"
#include "ui_registry.h"
#include "account.h"
#include <fstream>
#include <string>
#include <cstring>
#include "menu.h"
#include "mainmenu.h"
#include<QPixmap>
using namespace std;
/*!
 * \brief Конструктор класса Registry.
 * \param parent-указатель на класс-родитель.
 */
Registry::Registry(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Registry)
{
    fl1=fl2=fl3=false;
    ui->setupUi(this);
    QPixmap a (":/picha/Pichures/RegistryCreen.png");
    ui->label->setPixmap(a);
    setWindowTitle("\"Умный дом\":Регистрация");
}
/*!
 * \brief Деструктор класса Registry.
 */
Registry::~Registry()
{
    delete ui;
}
/*!
 * \brief Метод класса Registry, отвечающий за регистрацию пользователя.
 */
void Registry::on_go_clicked()
{
    int k;
    char *str;
    bool err=false;
    bool adm=false;
    account a;
    double m;

    if(ui->pass1->text() !=ui->pass2->text())
    {
        ui->warning_log_2->setStyleSheet("QLabel {background-color: rgb(204, 0, 0);color: rgb(238, 238, 236);}");
        ui->warning_log_2->setText("\t   Пароли не совпадают.");
        err=true;
    }
    else
    {
        ui->warning_log_2->setStyleSheet("QLabel {background-color:rgb(32, 180, 28);color: rgb(238, 238, 236);}");
        ui->warning_log_2->setText("\t   Пароли совпадают.");
    }
    std::string login =(ui->Name->text()).toStdString();
    ifstream file;
    file.open("logins.dat",ios_base::binary);
    if(!file.is_open())
    {
        adm=true;
        ui->warning_log->setStyleSheet("QLabel {background-color:rgb(32, 180, 28);color: rgb(238, 238, 236);}");
        ui->warning_log->setText("\t           Логин свободен.");
    }
    else
    {
        while(1)
        {
            file.read((char*)&k,sizeof(int));
            str=new char[k+1];
            file.read((char*)str,sizeof(char)*k);
            strcat(str,"\0");
            if(!strcmp(str,login.c_str()))
            {
                ui->warning_log->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
                ui->warning_log->setText("\t            Логин занят.");
                err=true;
                delete []str;
                file.close();
                break;
            }
            else if(file.eof())
            {
                ui->warning_log->setStyleSheet("QLabel {background-color:rgb(32, 180, 28);color: rgb(238, 238, 236);}");
                ui->warning_log->setText("\t           Логин свободен.");
                file.close();
                break;
            }
            file.read((char*)&k,sizeof(int));
            str=new char[k];
            file.read((char*)str,sizeof(char)*k);
            delete []str;
            file.read((char*)&k,sizeof(int));
            file.read((char*)&m,sizeof(double));
        }
    }
    if(err==false)
    {
        double m=0;
        std::string pass =(ui->pass1->text()).toStdString();
        a.regist(login,pass,adm,0);
        mainmenu * w=new mainmenu(login,pass,adm,m,0);
        delete this;
        w->show();
    }
}
/*!
 * \brief Метод класса Registry, отвечающий за открытие окна авторизации.
 */
void Registry::on_go_2_clicked()
{
    menu *w=new menu;
    delete this;
    w->show();

}
/*!
 * \brief Метод класса Registry, отвечающий за очищение поля логина под ввод.
 */
void Registry::on_Name_selectionChanged()
{
    if(fl1==false)
    {
        ui->Name->clear();
        fl1=true;
    }
}
/*!
 * \brief Метод класса Registry, отвечающий за очищение поля пароля под ввод.
 */
void Registry::on_pass1_selectionChanged()
{
    if(fl2==false)
    {
        ui->pass1->clear();
        fl2=true;
        ui->pass1->setEchoMode(QLineEdit::EchoMode::Password);
    }
}
/*!
 * \brief Метод класса Registry, отвечающий за очищение поля повторного пароля под ввод.
 */
void Registry::on_pass2_selectionChanged()
{
    if(fl3==false)
    {
        ui->pass2->clear();
        fl3=true;
        ui->pass2->setEchoMode(QLineEdit::EchoMode::Password);
    }
}
