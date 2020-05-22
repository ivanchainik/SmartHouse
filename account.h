/*!
  \file
  \brief Заголовочный файл с описанием класса.

  Данный файл содержит описание класса account.
*/
#ifndef ACCOUNT_H
#define ACCOUNT_H
#include<string>
#include<vector>
#include"house.h"
using namespace std;
/*!
 * \brief Класс содержащий все методы для работы с аккаунтом. Классов наследников не имеет.
 */
class account
{
private:
    string login;///< Логин.
    string password;///< Пароль.
    bool admin;///< Переключатель администратора.
    double money;///< Деньги за оплату.
    vector<house> homes;///< Дома, принадлежащие пользователю.
public:
    account();
    account(const string &_login,const string &_pass,const bool &_adm,const double &_money);
    void regist(const string &login,const string &pass,bool &adm,const double &_money);
    bool get_adm();
    void save_all();
    string get_login();
    string get_pass();
    double  get_money();
    void do_adm(bool _adm);
    void in_vector(house &a);
    void read_all();
    void delete_house(const house &a);
    vector<house> get_homes();
    int delete_acc();
    void delete_all_house();
    void home_account();
    void off_devais(house &a,int i);
    void delete_devais(house &a,const room exp,const devais dev_);
    void push_devais(devais &new_dev,house &a,const room exp);
    void add_money(const double a);
    account(string &str);
    void put_money(double a);
};

#endif // ACCOUNT_H
