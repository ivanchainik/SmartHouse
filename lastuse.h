/*!
  \file
  \brief Файл, содержащий класс LastUse.
  */

#ifndef LASTUSE_H
#define LASTUSE_H
#include "house.h"
#include "account.h"
#include <string>
/*!
 * \brief Класс ,отвечающий за оплату и статистику.
 */
class LastUse
{
private:
    account user;///<Пользователь.
    int day;///<День последнего захода.
    int month;///<Месяц последнего захода.
    int hour;///<Час последнего захода.
    bool fl;///<Флаг ,показывающий оплату.
    void save_one(ofstream &file);
    void oplata();
public:
    LastUse ();
    LastUse(string login,bool &ok,int a[]);
    void put_account(account &_user);
    void load();
    string get_login();
    void dell_acc();
    double get_money();
};

#endif // LASTUSE_H
