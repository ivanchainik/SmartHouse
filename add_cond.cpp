/*!
  \file
  \brief Файл содержащий описание методов класса add_cond.
  */
#include "add_cond.h"
#include "ui_add_cond.h"
/*!
 * \brief Конструктор класса :add_cond.
 * \param a-Дом , в котором происходят изменения.
 * \param b-Комната , в которой происходят изменения.
 * \param parent-Указатель на класс родитель.
 */
add_cond::add_cond(house &a, room &b, work_sen *parent):
    QWidget(parent),
    ui(new Ui::add_cond)
{
    dom=a;
    komn=b;
    par=parent;
    par->close();
    ui->setupUi(this);
    setWindowTitle("\"Умный дом\":Установка кондиционера.");
    QPixmap pix(":/picha/Pichures/cond.png");
}
/*!
 * \brief Деструктор класса add_cond.
 */
add_cond::~add_cond()
{
    delete ui;
}
/*!
 * \brief Метод класса add_cond ,отвечающий за выход из окна.
 */
void add_cond::on_back_clicked()
{
    delete this;
    par->show();
    par->obnov();
}
/*!
 * \brief Метод класса add_cond ,отвечающий за создание кондиционера.
 */
void add_cond::on_enter_clicked()
{
    bool warn=false;
    double energy;
    double temp;
    bool ok;
    energy=ui->electr->text().toDouble(&ok);
    if(!ok)
    {
        warn=true;
        ui->warning->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
        ui->warning->setText("Требовалось ввести число.");
    }
    else
    {
        ui->warning->setStyleSheet("QLabel {background-color: rgba(204, 0, 0,1)");
        ui->warning->clear();
    }
    temp=ui->temp->text().toDouble(&ok);
    if(!ok)
    {
        warn=true;
        ui->warning_2->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
        ui->warning_2->setText("Требовалось ввести число.");
    }
    else
    {
        ui->warning_2->setStyleSheet("QLabel {background-color: rgba(204, 0, 0,1)");
        ui->warning_2->clear();
    }
    if((!komn.get_sensor(1).get_norm() && komn.get_sensor(1).get_have() &&komn.get_sensor(1).get_on()) ||\
            (!komn.get_sensor(2).get_norm() && komn.get_sensor(2).get_have() &&komn.get_sensor(2).get_on()))
    {
            warn=true;
            ui->warning_3->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
            ui->warning_3->setText("Нельзя включить прибор при сработавших датчиках.");
    }
    else
    {
            ui->warning_3->setStyleSheet("QLabel {background-color: rgba(204, 0, 0,1)");
            ui->warning_3->clear();
    }
    if(warn==false)
    {
        ok=true;
        warn=ui->on_true->isChecked();
        account user;
        user.read_all();
        komn.get_temp_sen().put_temp(warn,temp,ok);
        komn.get_temp_sen().put_kom(1,energy);
        dom.delete_room(komn);
        dom.in_vector(komn);
        user.delete_house(dom);
        user.in_vector(dom);
        user.save_all();
        ui->warning_2->setStyleSheet("QLabel {background-color:rgb(32, 180, 28);color: rgb(238, 238, 236);}");
        ui->warning_2->setText("Успешно подключен.");
    }
}
