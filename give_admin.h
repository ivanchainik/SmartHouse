/*!
  \file
  \brief Данный файл содержит описание класса Give_admin.
 */
#ifndef GIVE_ADMIN_H
#define GIVE_ADMIN_H
#include<vector>
#include <QWidget>
#include"account.h"
#include "mainmenu.h"
namespace Ui {
class Give_admin;
}

/*!
 * \brief Класс отвечающий за графический интерфейс получения прав администратора.
 */
class Give_admin : public QWidget
{
    Q_OBJECT

public:
    explicit Give_admin(account &user,mainmenu *parent = 0);
    ~Give_admin();

private slots:
    void on_back_clicked();

    void on_day_clicked();

    void on_otday_clicked();

private:
    mainmenu *mane;///< Указатель на класс родитель.
    account user1;///< Аккаунт, в котором происходит изменение.
    Ui::Give_admin *ui;///< Графический интерфейс класса Give_admin.
    int value_adm;///< Значение показывающее является данный пользаватель администратором.
    std::vector<account> users;///> Список аккаутов.
    void in_vector();
    void obnov();
};

#endif // GIVE_ADMIN_H
