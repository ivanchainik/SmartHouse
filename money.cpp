/*!
  \file
  \brief Файл, содержащий описание методов класса money.
  */
#include "money.h"
#include "ui_money.h"
#include "account.h"
#include "mainmenu.h"
/*!
 * \brief Конструктор класса money.
 * \param a - пользователь.
 * \param parent -указатель на родительский класс.
 */
money::money(account &a,mainmenu *parent) :
    QWidget(parent),
    ui(new Ui::money)
{
    ui->setupUi(this);
    user=a;
    par=parent;
    obnov();
    setWindowTitle("\"Умный дом\":Банковский счет.");
    QPixmap pix(":/picha/Pichures/money.png");
}
/*!
 * \brief Деструктор класса money.
 */
money::~money()
{
    delete ui;
}
/*!
 * \brief Метод класса money, добавляющий 500 на счет пользователя.
 */
void money::on_add_500_clicked()
{
    user.add_money(500);
    obnov();
}
/*!
 * \brief Метод класса money, добавляющий 1000 на счет пользователя.
 */
void money::on_add_1000_clicked()
{
    user.add_money(1000);
    obnov();
}
/*!
 * \brief Метод класса money, добавляющий 5000 на счет пользователя.
 */
void money::on_add_5000_clicked()
{
    user.add_money(5000);
    obnov();
}
/*!
 * \brief Метод класса money, отвечающий за обновление окна.
 */
void money::obnov()
{
    ui->check->setText(QString("%2").arg(user.get_money()));
   par->obnov(user.get_login(),user.get_pass(),user.get_adm(),user.get_money());
}
/*!
 * \brief Метод класса money, отвечающий за выход из окна.
 */
void money::on_back_clicked()
{
    delete this;
}
