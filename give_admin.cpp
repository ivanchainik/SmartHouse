/*!
\file
\brief Исходный файл, содержащий описание методов класса Give_admin.
*/
#include "give_admin.h"
#include "ui_give_admin.h"
#include <vector>
#include <fstream>
#include <string>
#include "account.h"
#include "mainmenu.h"
/*!
 * \brief Конструктор класса Give-admin.
 * \param user Передает информацию об аккаунте которому нуно дать права администратора.
 * \param parent
 */
Give_admin::Give_admin(account &user,mainmenu *parent) :
    QWidget(parent),
    ui(new Ui::Give_admin)
{
        mane=parent;
        user1=user;
        ui->setupUi(this);
        this->obnov();
        setWindowTitle("\"Умный дом\":Добавление/удаление администратора.");
        QPixmap pix(":/picha/Pichures/give_admin.png");
}
/*!
 * \brief Деструктор класса Give_admin.
 */
Give_admin::~Give_admin()
{
   delete ui;
}
/*!
 * \brief Метод загружающий аккаунты в вектор.
 */
void Give_admin::in_vector()
{
    ifstream file;
    char *str[2];
    int k;
    double m;
    value_adm=0;
    std::string _login;
    std::string _pass;
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
            file.read((char*)&k,sizeof(int));
            if(k==1)value_adm++;
            file.read((char*)&m,sizeof(double));
            _login=str[0];
            _pass=str[1];
            delete [] str[0];
            delete [] str[1];
            account a(_login,_pass,k,m);
            users.push_back(a);
     }
     file.close();
}
/*!
 * \brief Метод обновляющий страницу.
 */
void Give_admin::obnov()
{
    QString str;
    this->in_vector();
    auto first=users.begin();
    auto last =users.end();
    for( ;first !=last;first++)
    {
        if(first==users.begin()){
            str=str.fromStdString(first->get_login());
            QListWidgetItem *a=new QListWidgetItem(str);
            ui->Users->addItem(a);
            ui->Users->setCurrentItem(a);
            continue;
        }
        str=str.fromStdString(first->get_login());
        ui->Users->addItem(str);
    }
}
/*!
 * \brief Метод возвращающий на предыдущую страницу.
 */
void Give_admin::on_back_clicked()
{
    delete this;
}
/*!
 * \brief Метод дающий права администратора.
 */
void Give_admin::on_day_clicked()
{
    std::string _login=ui->Users->currentItem()->text().toStdString();
    auto first=users.begin();
    auto last=users.end();
    for(;first !=last;first++)
    {
        if(_login==first->get_login())break;
    }
    if(first->get_adm()==true)
    {
        ui->Warning->setStyleSheet("QLabel {background-color: rgb(204, 0, 0);color: rgb(238, 238, 236);}");
        ui->Warning->setText("\tДанный пользователь уже администратор.");
    }
    else
    {
        first->do_adm(true);
        ofstream file;
        file.open("logins.dat",ios_base::binary | ios_base::trunc);
        file.close();
        for(first=users.begin();first!=last;first++)
        {
            bool a=first->get_adm();
            first->regist(first->get_login(),first->get_pass(),a,first->get_money());
        }
        ui->Warning->setStyleSheet("QLabel {background-color: rgb(32, 180, 28);color: rgb(238, 238, 236);}");
        value_adm++;
        mane->obnov(user1.get_login(),user1.get_pass(),true,user1.get_money());
        ui->Warning->setText("\tДанный пользователь стал администратором.");
    }
}
/*!
 * \brief Метод забирающий права администратора.
 */
void Give_admin::on_otday_clicked()
{
    std::string _login=ui->Users->currentItem()->text().toStdString();
    auto first=users.begin();
    auto last=users.end();
    for(;first !=last;first++)
    {
        if(_login==first->get_login())break;
    }
    if(first->get_adm()==false)
    {
        ui->Warning->setStyleSheet("QLabel {background-color: rgb(204, 0, 0);color: rgb(238, 238, 236);}");
        ui->Warning->setText("\tДанный пользователь не администратор.");
    }
    else if(value_adm==1)
    {
        ui->Warning->setStyleSheet("QLabel {background-color: rgb(204, 0, 0);color: rgb(238, 238, 236);}");
        ui->Warning->setText("\tНельзя удалить единственного администратора.");
    }
    else
    {
        first->do_adm(false);
        if(first->get_login()==user1.get_login())
        {
            user1.do_adm(false);
            mane->obnov(user1.get_login(),user1.get_pass(),user1.get_adm(),user1.get_money());
        }
        ofstream file;
        file.open("logins.dat",ios_base::binary | ios_base::trunc);
        file.close();
        for(first=users.begin();first!=last;first++)
        {
            bool a=first->get_adm();
            first->regist(first->get_login(),first->get_pass(),a,first->get_money());
        }
        ui->Warning->setStyleSheet("QLabel {background-color: rgb(32, 180, 28);color: rgb(238, 238, 236);}");
        value_adm--;
        ui->Warning->setText("\tДанный администратор стал обычным пользователем.");

    }
}
