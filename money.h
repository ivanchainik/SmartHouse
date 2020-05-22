/*!
  \file
  \brief Файл, содержащий класс money.
  */
#ifndef MONEY_H
#define MONEY_H

#include <QWidget>
#include "account.h"
#include"mainmenu.h"
namespace Ui {
class money;
}
/*!
 * \brief Класс,отвечающий за работу окна банковского счета.
 */
class money : public QWidget
{
    Q_OBJECT

public:
    explicit money(account &a,mainmenu *parent);
    ~money();

private slots:
    void on_add_500_clicked();

    void on_add_1000_clicked();

    void on_add_5000_clicked();

    void on_back_clicked();

private:
    Ui::money *ui;///<Графический интерфейс класса money.
    account user;///<Пользователь.
    mainmenu *par;///<Указатель на родительский класс.
    void obnov();
};

#endif // MONEY_H
