/*!
\file
\brief Исходный файл, содержащий описание всех методов класса add_house.
  */
#include "add_house.h"
#include "ui_add_house.h"
#include "house.h"
#include "add_room.h"
#include "mainmenu.h"
/*!
 * \brief Конструктор класса add_house.
 * \param _user Аккаунт, в котором происходит изменения.
 * \param parent Указатель на класс родитель.
 */
Add_house::Add_house(account &_user,mainmenu *parent) :
    QWidget(parent),
    ui(new Ui::Add_house)
{
    ParWin=parent;
    user=_user;
    ui->setupUi(this);
    setWindowTitle("\"Умный дом\":Добаление дома.");
    QPixmap pix(":/picha/Pichures/house.png");
}
/*!
 * \brief Деструктор класса add_house.
 */
Add_house::~Add_house()
{
    delete ui;
}
/*!
 * \brief Метод класса add_house, отвечающий за выход из окна.
 */
void Add_house::on_back_clicked()
{
    delete this;
}
/*!
 * \brief Метод класса add_house, отвечающий за создание дома.
 */
void Add_house::on_enter_clicked()
{
    house a;
    bool warn=false;
    bool warn1;
    int _num_home;
    int _flat;
    int value_room;
    std::string _street;
    if((_street=ui->_street->text().toStdString()).size() ==0)
    {
        warn=true;
        ui->warning->setStyleSheet("QLabel {background-color: rgb(204, 0, 0);color: rgb(238, 238, 236);}");
        ui->warning->setText("Название улицы не может быть пустым.");

    }
    else
    {
        ui->warning->setStyleSheet("QLabel {background-color: rgba(204, 0, 0,1)");
        ui->warning->clear();
    }
    _num_home=ui->_num_house->text().toInt(&warn1);
    if(!warn1)
    {
        warn=true;
        ui->warning_2->setStyleSheet("QLabel {background-color: rgb(204, 0, 0);color: rgb(238, 238, 236);}");
        ui->warning_2->setText("Требуется ввести целое число.");
    }
    else if(_num_home<=0)
    {
        warn=true;
        ui->warning_2->setStyleSheet("QLabel {background-color: rgb(204, 0, 0);color: rgb(238, 238, 236);}");
        ui->warning_2->setText("Номер дома должен быть больше нуля.");
    }
    else
    {
        ui->warning_2->setStyleSheet("QLabel {background-color: rgba(0, 0, 0,1)");
        ui->warning_2->clear();
    }
     _flat=ui->_flat->text().toInt(&warn1);
     if(!warn1)
     {
         warn=true;
         ui->warning_3->setStyleSheet("QLabel {background-color: rgb(204, 0, 0);color: rgb(238, 238, 236);}");
         ui->warning_3->setText("Требуется ввести целое число.");
     }
     else if(_flat<=0)
     {
         warn=true;
         ui->warning_3->setStyleSheet("QLabel {background-color: rgb(204, 0, 0);color: rgb(238, 238, 236);}");
         ui->warning_3->setText("Номер квартиры должен быть больше нуля.");
     }
     else
     {
         ui->warning_3->setStyleSheet("QLabel {background-color: rgba(0, 0, 0,1)");
         ui->warning_3->clear();
     }
     value_room=ui->value_rooms->text().toInt(&warn1);
     if(!warn1)
     {
         warn=true;
         ui->warning_4->setStyleSheet("QLabel {background-color: rgb(204, 0, 0);color: rgb(238, 238, 236);}");
         ui->warning_4->setText("Требуется ввести целое число.");
     }
     else if(value_room<=0)
     {
         warn=true;
         ui->warning_4->setStyleSheet("QLabel {background-color: rgb(204, 0, 0);color: rgb(238, 238, 236);}");
         ui->warning_4->setText("количество комнат должно быть больше нуля.");
     }
     else
     {
         ui->warning_4->setStyleSheet("QLabel {background-color: rgba(0, 0, 0,1)");
         ui->warning_4->clear();
     }
     warn1=false;
     account vrem;
     vrem.read_all();
     std::vector<house>::iterator first=vrem.get_homes().begin();
     std::vector<house>::iterator last=vrem.get_homes().end();
     for(;first !=last;first++)
     {
            if(first->get_street()==_street && first->get_num()==_num_home && first->get_flat()==_flat)
            {
                warn=true;
                warn1=true;
                ui->warning_5->setStyleSheet("QLabel {background-color: rgb(204, 0, 0);color: rgb(238, 238, 236);}");
                ui->warning_5->setText("\tДом с такими данными уже существует.");
            }
     }
     if(warn1==false)
     {
         ui->warning_5->setStyleSheet("QLabel {background-color: rgba(0, 0, 0,1)");
         ui->warning_5->clear();
     }

     if(warn ==false)
     {
         int k=1;
         bool co [3];
         double r[6] {0,0,0,0,0,0};
         std::string _login=user.get_login();
         a.put_house(_flat,_street,_login,_num_home);
         co[0]=ui->Water->isChecked();
         co[1]=ui->electr->isChecked();
         co[2]=ui->gas->isChecked();
         a.new_couters(co[0],co[1],co[2]);
         a.last_coun(r);
         add_room *c=new add_room(user,a,k,value_room,ParWin);
         delete this;
         c->setWindowFlag(Qt::Dialog);
         c->setWindowModality(Qt::WindowModal);
         c->show();

     }

}
