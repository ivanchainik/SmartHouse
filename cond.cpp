/*!
  \file
  \brief Файл ,содержащий описания методов класса cond.
  */
#include "cond.h"
#include "ui_cond.h"
#include "account.h"
#include "work_sen.h"
/*!
 * \brief Конструктор класса kond.
 * \param _dom -дом,в котором включают кондиционер.
 * \param _komn -комната,в которой включают кондиционер.
 * \param parent -указатель на родительский класс.
 */
cond::cond(house &_dom,room &_komn,work_sen *parent) :
    QWidget(parent),
    ui(new Ui::cond)
{
    ui->setupUi(this);
    dom=_dom;
    komn=_komn;
    par=parent;
    par->close();
    setWindowTitle("\"Умный дом\":Включение кондиционера.");
    QPixmap pix(":/picha/Pichures/condl.png");
}
/*!
 * \brief Деструктор класса cond.
 */
cond::~cond()
{
    delete ui;
}
/*!
 * \brief Метод класса cond, включающий кондиционер.
 */
void cond::on_enter_clicked()
{
    double temp;
    bool ok;
    temp=ui->temp->text().toDouble(&ok);
    if(!ok)
    {
        ui->warning->setStyleSheet("QLabel {background-color:rgb(204,0,0);color: rgb(238, 238, 236);}");
        ui->warning->setText("Требовалось ввести число.");
    }
    else
    {
        account user;
        user.read_all();
        komn.get_temp_sen().put_temp(ok,temp,ok);
        dom.delete_room(komn);
        dom.in_vector(komn);
        user.delete_house(dom);
        user.in_vector(dom);
        user.save_all();
        ui->warning->setStyleSheet("QLabel {background-color:rgb(32, 180, 28);color: rgb(238, 238, 236);}");
        ui->warning->setText("Успешно включен.");
    }
}
/*!
 * \brief Метод класса cond, отвечающий за закрытие окна.
 */
void cond::on_back_clicked()
{
    delete this;
    par->show();
    par->obnov();
}
