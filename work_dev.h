/*!
  \file
  \brief Файл ,содержащий класс work_dev.
 */
#ifndef WORK_DEV_H
#define WORK_DEV_H

#include <QWidget>
#include "mainmenu.h"
namespace Ui {
class work_dev;
}
/*!
 * \brief Класс ,отвечающий за отображение окна работы с приборами.
 */
class work_dev : public QWidget
{
    Q_OBJECT

public:
    explicit work_dev(account &_user,std::string &adress,mainmenu *parent = 0);
    ~work_dev();
    void ok_new_dev();
    void obnov();


private slots:

    void on_add_dev_clicked();

    void on_on_true_clicked();

    void on_on_false_clicked();

    void on_change_dev_clicked();

    void on_info_dev_clicked();

    void on_delete_pr_clicked();

    void on_back_clicked();

    void on_roomlist_itemSelectionChanged();


private:
    Ui::work_dev *ui;///<Графический интерфейс класса work_dev.
    account user;///<Пользователь.
    house dom;///<Дом,с которым идет работа.
    mainmenu *par;///<Указатель на родительский класс.
    room komn;///<Комната,с которой идет работа.
    void listroom();
};

#endif // WORK_DEV_H
