/*!
  \file
  \brief Файл ,содержащий класс work_counter.
 */
#ifndef WORK_COUNTER_H
#define WORK_COUNTER_H

#include <QWidget>
#include "mainmenu.h"
#include "account.h"
#include "string"
namespace Ui {
class work_counter;
}
/*!
 * \brief Класс, отвечающий за окно работы с счетчиками.
 */
class work_counter : public QWidget
{
    Q_OBJECT

public:
    explicit work_counter(account &a,std::string &_adress,mainmenu *parent);
    ~work_counter();

private slots:
    void on_pushButton_clicked();

    void on_on_true_clicked();

    void on_on_false_clicked();

    void on_have_true_clicked();

    void on_have_false_clicked();

    void on_norm_true_clicked();

    void on_norm_false_clicked();

private:
    Ui::work_counter *ui;///<Графический интерфейс класса work_counter.
    mainmenu *par;///<Указатель на родительский класс.
    house home;///<Дом с которым идет работа.
    account user;///<Пользователь.
    std::string adress;///<Адрес дома.
    void obnov();
    void clear_electr();
    void clear_gas();
    void clear_water();


};

#endif // WORK_COUNTER_H
