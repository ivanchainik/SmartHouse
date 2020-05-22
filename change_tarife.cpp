/*!
  \file
  \brief Файл ,содержащий описания методов класса change_tarife.
 */
#include "change_tarife.h"
#include "ui_change_tarife.h"
#include "tarif.h"
/*!
 * \brief Конструктор класса change_tarife.
 * \param parent -указатель на родительский класс.
 */
change_tarife::change_tarife(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::change_tarife)
{
    tarif a;
    QString str;
    ui->setupUi(this);
    str=QString("%2").arg(a.get_electr());
    ui->electrstr->setText(str);
    str=QString("%2").arg(a.get_water());
    ui->waterstr->setText(str);
    str=QString("%2").arg(a.get_gaz());
    ui->gasstr->setText(str);
    str=QString("%1").arg(a.get_dayofpay());
    ui->dayofpaystd->setText(str);
    setWindowTitle("\"Умный дом\":Изменение тарифов.");
    QPixmap pix(":/picha/Pichures/change_tarife.png");
}
/*!
 * \brief Деструктор класса change_tarife.
 */
change_tarife::~change_tarife()
{
    delete ui;
}
/*!
 * \brief Метод класса change_tarife ,отвечающий за изменение тарифов.
 */
void change_tarife::on_pushButton_2_clicked()
{
    QString str=ui->electrstr->text();
    bool warning[4];
    double value[3];
    int day;
    ui->Yes->setText("");
    value[2]=str.toDouble(&warning[0]);
    if(warning[0])
    {
        ui->warningelectr->setText("");
    }
    else
    {
        ui->warningelectr->setText("Ошибка ввода");

    }
    str=ui->waterstr->text();
    value[1]=str.toDouble(&warning[1]);
    if(warning[1])
    {
        ui->warningwater->setText("");
    }
    else
    {
        ui->warningwater->setText("Ошибка ввода");
    }
    str=ui->gasstr->text();
    value[0]=str.toDouble(&warning[2]);
    if(warning[2])
    {
        ui->warningas->setText("");
    }
    else
    {
        ui->warningas->setText("Ошибка ввода");
    }
    str=ui->dayofpaystd->text();
    day=str.toInt(&warning[3]);
    if (day<=0 || day>31)
    {
        warning[3]=false;
    }
    if(warning[3])
    {
        ui->warningday->setText("");
    }
    else
    {
        ui->warningday->setText("Ошибка ввода");
    }
    if(warning[0] && warning[1] && warning[2] && warning[3])
    {
        tarif a;
        a.change_tarif(1,value[0]);
        a.change_tarif(2,value[1]);
        a.change_tarif(3,value[2]);
        a.change_tarif(day);
        ui->Yes->setText("Изменения успешны.");
    }
}
/*!
 * \brief Метод класса change_tarife ,отвечающий за выход из окна.
 */
void change_tarife::on_pushButton_clicked()
{
    delete this;
}
