/*!
  \file
  \brief Файл,содержащий класс work_sen.
  */
#ifndef WORK_SEN_H
#define WORK_SEN_H

#include <QWidget>
#include "mainmenu.h"
#include "account.h"
namespace Ui {
class work_sen;
}
/*!
 * \brief Класс,отвечающий за окно работы с датчиками.
 */
class work_sen : public QWidget
{
    Q_OBJECT

public:
    explicit work_sen(const std::string _adress,const account &_user,mainmenu *parent = 0);
    ~work_sen();
    void obnov();

private slots:
    void on_back_clicked();

    void on_roomlist_itemSelectionChanged();

    void on_have_true_clicked();

    void on_have_false_clicked();

    void on_on_true_clicked();

    void on_on_false_clicked();

    void on_simulat_clicked();

    void on_cond_have_true_clicked();

    void on_cond_have_false_clicked();

    void on_cond_on_but_clicked();

private:
    Ui::work_sen *ui;///<Графический интерфейс класса work_sen.
    account user;///<Пользователь.
    mainmenu *par;///<Указатель на родительский класс.
    house dom;///<Дом, с которым идет работа.
    room komn;///<Комната,с которой идет работа.
    std::string adress;///<Адрес дома.
    void roomlist();
    void clear_water();
    void clear_gas();
    void clear_temp();
};

#endif // WORK_SEN_H
