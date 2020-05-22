/*!
\file
\brief Исходный файл, содержащий описание методов класса add_room.
*/
#include "add_room.h"
#include "ui_add_room.h"
#include "room.h"
#include "account.h"
#include "mainmenu.h"
#include "temperature.h"
/*!
 * \brief Конструктор класса add_room.
 * \param a Аккаунт, в котором происходят изменения.
 * \param dom Дом, в котором происходит изменения.
 * \param _numberofroom Номер комнаты, которую нужно добавить.
 * \param allroom Общее количество комнат в доме.
 * \param parent Указатель на класс родитель.
 */
add_room::add_room(account &a,house &dom,int &_numberofroom,int &allroom,mainmenu *parent) :
    QWidget(parent),
    ui(new Ui::add_room)
{
    auser=a;
    ui->setupUi(this);
    ui->numberofroom->setText(QString("%1").arg(_numberofroom));
    allnum=allroom;
    num=_numberofroom;
    par=parent;
    home=dom;
    setWindowTitle("\"Умный дом\":Добаление комнаты.");
    QPixmap pix(":/picha/Pichures/add_room.png");
}
/*!
 * \brief Деструктор класса add_room.
 */
add_room::~add_room()
{
    delete ui;
}
/*!
 * \brief Метод класса add_room, отвечающий за создание комнаты.
 */
void add_room::on_enter_clicked()
{
    bool ok;
    double _area;
    int type;
    bool warn=false;
    _area=ui->Area->text().toDouble(&ok);
    if(ok==false)
    {
        warn=true;
        ui->warning_2->setStyleSheet("QLabel {background-color: rgb(204, 0, 0);color: rgb(238, 238, 236);}");
        ui->warning_2->setText("\tТребуется ввести число.");
    }
    else if(_area<=0)
    {
        warn=true;
        ui->warning_2->setStyleSheet("QLabel {background-color: rgb(204, 0, 0);color: rgb(238, 238, 236);}");
        ui->warning_2->setText("\tПлощадь должна быть больше нуля");
    }
    else
    {
        ui->warning_2->setStyleSheet("QLabel {background-color: rgba(204, 0, 0,1)");
        ui->warning_2->clear();
    }
    if(ui->bathroom->isChecked())
    {
        ui->warning_2->setStyleSheet("QLabel {background-color: rgba(204, 0, 0,1)");
        ui->warning_2->clear();
        type=1;
    }
    else if(ui->kitchen->isChecked())
    {
        ui->warning_2->setStyleSheet("QLabel {background-color: rgba(204, 0, 0,1)");
        ui->warning_2->clear();
        type=2;
    }
    else if(ui->living->isChecked())
    {
        ui->warning_2->setStyleSheet("QLabel {background-color: rgba(204, 0, 0,1)");
        ui->warning_2->clear();
        type=3;
    }
    else
    {
        warn=true;
        ui->warning_2->setStyleSheet("QLabel {background-color: rgb(204, 0, 0);color: rgb(238, 238, 236);}");
        ui->warning_2->setText("\tТребуется выбрать тип комнаты.");
    }
    if(warn !=true)
    {
        room a;
        a.put_room(type,_area);
        bool _on;
        bool _norm=true;
        double _proc=0;
        int k=0;
        _on=ui->checkBox_2->isChecked();
        a.get_sensor(1).put_sencor(_on,_norm,_proc);
        a.get_sensor(1).on_off(_on);
        _on=ui->checkBox_3->isChecked();
        a.get_sensor(2).put_sencor(_on,_norm,_proc);
        a.get_sensor(2).on_off(_on);
        _on=ui->checkBox_4->isChecked();
        a.get_temp_sen().put_sencor(_on,_norm,_proc);
        a.get_temp_sen().on_off(_on);
        _on=false;
        _proc=abs(rand()%15+10);
        a.get_temp_sen().put_temp(_on,_proc,_on);
        a.get_temp_sen().put_kom(1,k);
        home.in_vector(a);
        if(num==allnum)
        {
               auser.delete_all_house();
               auser.in_vector(home);
               auser.read_all();
               auser.save_all();
               par->obnov(auser.get_login(),auser.get_pass(),auser.get_adm(),auser.get_money());
               delete this;
        }
        else
        {
                num++;
                add_room *a=new add_room(auser,home,num,allnum,par);
                delete this;
                a->setWindowFlag(Qt::Dialog);
                a->setWindowModality(Qt::WindowModal);
                a->show();
        }
    }
}
