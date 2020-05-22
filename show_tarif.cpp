/*!
  \file
  \brief Файл,содержащий описание методов класса show_tarif.
  */
#include "show_tarif.h"
#include "ui_show_tarif.h"
#include "tarif.h"
/*!
 * \brief Конструктор класса show_tarif.
 * \param parent -указатель на родительский класс.
 */
show_tarif::show_tarif(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::show_tarif)
{
    tarif show_;
    ui->setupUi(this);
    QString str ;
    str=QString("%2").arg(show_.get_electr());
    ui->electstr->setText(str);
    str=QString("%2").arg(show_.get_water());
    ui->waterstr->setText(str);
    str=QString("%2").arg(show_.get_gaz());
    ui->gasstr->setText(str);
    str=QString("%1").arg(show_.get_dayofpay());
    ui->dayofpaystr->setText(str);
    str=QString("%1").arg(show_.days_to_pay());
    ui->daytopaystr->setText(str);
    setWindowTitle("\"Умный дом:\"Информация о тарифах");
    QPixmap pix(":/picha/Pichures/show_tarif.png");

}
/*!
 * \brief Деструктор класса show_tarif.
 */
show_tarif::~show_tarif()
{
    delete ui;
}
/*!
 * \brief Метод класса show_tarif, отвечающий за закрытие окна.
 */
void show_tarif::on_back_clicked()
{
   delete this;
}
