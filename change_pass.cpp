/*!
    \file
    \brief Файл ,содержащий описание методов класса change_pass.
  */
#include "change_pass.h"
#include "ui_change_pass.h"
#include <string>
#include <fstream>
#include <vector>
#include "account.h"
#include "mainmenu.h"
/*!
 * \brief Конструктор класса change_pass.
 * \param user -Аккаунт ,в котором меняем пароль.
 * \param parent -Указатель на родительский класс.
 */
change_pass::change_pass(account &user,mainmenu *parent) :
    QWidget(parent),
    ui(new Ui::change_pass)
{
    a=parent;
    user1=user;
    ui->setupUi(this);
    ui->pass1->setEchoMode(QLineEdit::EchoMode::Password);
    ui->pass2->setEchoMode(QLineEdit::EchoMode::Password);
    setWindowTitle("\"Умный дом\":Смена пароля");
    QPixmap pix(":/picha/Pichures/change_pass.png");
}
/*!
 * \brief Деструктор класса change_pass.
 */
change_pass::~change_pass()
{
    delete ui;
}
/*!
 * \brief Метод класса change_pass ,отвечающий за выход из окна.
 */
void change_pass::on_back_clicked()
{
    a->obnov(user1.get_login(),user1.get_pass(),user1.get_adm(),user1.get_money());
    delete this;
}
/*!
 * \brief Метод класса change_pass, отвечающий за смену пароля.
 */
void change_pass::on_pushButton_clicked()
{
    if(ui->pass1->text()==ui->pass2->text())
    {
        std::vector<account> all;
        std::string newpass =ui->pass1->text().toStdString();
        ifstream file;
        std::string _login;
        std::string _pass;
        int k;
        double m;
        char* str[2];

        file.open("logins.dat",ios_base::binary);
        while(1)
        {
            file.read((char*)&k,sizeof(int));
            str[0]=new char[k+1];
            file.read((char*)str[0],sizeof(char)*k);
            strcat(str[0],"\0");
            if(file.eof())
            {
                delete str[0];
                break;
            }
            file.read((char*)&k,sizeof(int));
            str[1]=new char[k+1];
            file.read((char*)str[1],sizeof(char)*k);
            strcpy(str[1]+k,"\0");
            if(!strcmp(str[0],user1.get_login().c_str()))
            {
                delete str[1];
                str[1]=new char[newpass.size()+1];
                strcpy(str[1],newpass.c_str());
            }
            file.read((char*)&k,sizeof(int));
            file.read((char*)&m,sizeof(double));
            _login=str[0];
            _pass=str[1];
            delete [] str[0];
            delete [] str[1];
            account a(_login,_pass,k,m);
            all.push_back(a);
        }
        file.close();
        auto first=all.begin();
        auto last=all.end();
        ofstream file1;
        file1.open("logins.dat",ios_base::binary | ios_base::trunc);
        file1.close();
        for(;first !=last;first++)
        {
            bool adm=first->get_adm();
            first->regist(first->get_login(),first->get_pass(),adm,first->get_money());
        }
        ui->Warning->setStyleSheet("QLabel {background-color:rgb(32, 180, 28);color: rgb(238, 238, 236);}");
        ui->Warning->setText("\t   Пароль изменен.");
    }
    else
    {
        ui->Warning->setStyleSheet("QLabel {background-color: rgb(204, 0, 0);color: rgb(238, 238, 236);}");
        ui->Warning->setText("\t   Пароли не совпадают.");
    }
}
