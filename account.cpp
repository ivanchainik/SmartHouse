/*!
  \file
  \brief Исходный файл, содержащий все методы класса account.
*/
#include "account.h"
#include <fstream>
#include <iostream>
#include <string>
#include "house.h"
#include <algorithm>
#include <iterator>
#include<cstring>
#include <stdexcept>
using namespace std;
/*!
 * \brief Конструктор по умолчанию класса account.
 */
account::account()
{

}
/*!
 * \brief Конструктор класса account, который инициализирует элементы класса.
 * \param _login Переменная инициализирующая логин.
 * \param _pass Переменная инициализирующая пароль.
 * \param _adm Переменная инициализирующая значение администратора.
 * \param _money Переменная инициализирующая деньги, предназначенные для оплаты.
 */
account::account(const std::string &_login,const std::string &_pass,const bool &_adm,const double &_money)
{
    login=_login;
    password=_pass;
    admin=_adm;
    money=_money;
}
/*!
 * \brief Метод отвечающий за регистрацию аккаунта.
 * \param login Переменная, задающая логин пользователя.
 * \param pass Переменная, задающая пароль пользователя.
 * \param adm Переменная, отвечающая за то является ли пользователь администратором.
 * \param _money Переменная, задающая деньги необходимые для оплаты.
 */
void account::regist(const string &login,const string &pass,bool &adm,const double &_money)
{
    ofstream file;
    int k;
    double m=_money;
    file.open("logins.dat",ios_base::binary |ios_base::app);
    k=login.size();
    file.write((char*)&k,sizeof(int));
    file.write((char*)login.c_str(),sizeof(char)*k);
    k=pass.size();
    file.write((char*)&k,sizeof(int));
    file.write((char*)pass.c_str(),sizeof(char)*k);
    k=(adm==true)? 1:0;
    file.write((char*)&k,sizeof(int));
    file.write((char*)&m,sizeof(double));
    file.close();
}
/*!
 * \brief Метод, возвращающий значение флага администратора.
 * \return Флаг администратора.
 */
bool account::get_adm()
{
    return admin;
}
/*!
 * \brief Метод, записывающий данные аккаунта в бинарный файл.
 */
void account::save_all()
{
    ofstream file;
    string str;
    char h='h';
    int k;
    auto first=homes.begin();
    auto last=homes.end();

    file.open("information.dat",ios_base::binary);
    for(;first !=last;first++)
    {
        file.write((char*)&h,sizeof(char));
        str=first->get_owner();
        k=str.size();
        file.write((char*)&k,sizeof(int));
        file.write((char*)str.c_str(),sizeof(char)*k);
        str=first->get_street();
        k=str.size();
        file.write((char*)&k,sizeof(int));
        file.write((char*)str.c_str(),sizeof(char)*k);
        k=first->get_num();
        file.write((char*)&k,sizeof(int));
        k=first->get_flat();
        file.write((char*)&k,sizeof(int));
        first->save_all_help(file);
    }
    file.close();
}
/*!
 * \brief Метод, возвращающий логин пользователя.
 * \return Логин пользователя.
 */
std::string account::get_login()
{
    return login;
}
/*!
 * \brief Метод, возвращающий пароль.
 * \return Пароль пользователя.
 */
std::string account::get_pass()
{
    return password;
}
/*!
 * \brief Метод, возвращающий деньги, за оплату.
 * \return Деньги, необходимые для оплаты.
 */
double account:: get_money()
{
    return money;
}
/*!
 * \brief Метод, с помощью которого меняется флаг администратора.
 * \param Флаг администратора.
 */
void account::do_adm(bool _adm)
{
    admin=_adm;
}
/*!
 * \brief Метод, добавляющий новый дом в аккаунт.
 * \param a Класс домов, необходимых для добавления в аккаунт.
 */
void account::in_vector(house &a)
{
    homes.push_back(a);
}
/*!
 * \brief Метод считывающий данные из файла в аккаунт.
 */
void account::read_all()
{
    ifstream file;
    char h;
    file.open("information.dat",ios_base::binary);
    if(file.is_open())
    {
        file.read((char*)&h,sizeof(char));
        while(true)
        {
            if(file.eof())
            break;
            else
            {
                house a;
                a.read_all_help(file);
                homes.push_back(a);
            }
        }
    file.close();
    }
}
/*!
 * \brief Метод удаляющий дом из аккаунта.
 * \param a Класс дома, который нужно удалить.
 */
void account::delete_house(const house &a){
    vector<house>::iterator str=find(homes.begin(),homes.end(),a);
    homes.erase(str);
}
/*!
 * \brief Метод, возвращающий вектор домов.
 * \return Вектор домов.
 */
std::vector<house> account::get_homes()
{
    return homes;
}
/*!
 * \brief Метод, удаляющий аккаунт.
 * \return 0-при успешном удалении аккаунта.
 */
int account::delete_acc()
{

    ifstream file;
    int k;
    double m;
    char *str[2];
    int adm=0;
    std::string _login;
    std::string _pass;
    vector<account> all;
    file.open("logins.dat",ios_base::binary);
    while(1)
    {
        file.read((char*)&k,sizeof(int));
        str[0]=new char[k+1];
        file.read((char*)str[0],sizeof(char)*k);
        strcat(str[0],"\0");
        if(file.eof())
        {
            delete str[0];
            break;
        }
        file.read((char*)&k,sizeof(int));
        str[1]=new char[k+1];
        file.read((char*)str[1],sizeof(char)*k);
        strcpy(str[1]+k,"\0");
        file.read((char*)&k,sizeof(int));
        if(k==1) adm++;
        file.read((char*)&m,sizeof(double));
        _login=str[0];
        _pass=str[1];
        delete [] str[0];
        delete [] str[1];
        if (_login !=login)
        {
            account a(_login,_pass,k,m);
            all.push_back(a);
        }
    }
    if(adm==1 && admin==true) return 1;
    file.close();
    delete_all_house();
    read_all();
    auto first=homes.begin();
    auto last=homes.end();
    for(;first!=last;first++)
    {
        if(first->get_owner()==login)
        {
            delete_house(*first);
        }
    }
    save_all();
    auto first1=all.begin();
    auto last1=all.end();
    ofstream file1;
    file1.open("logins.dat",ios_base::binary | ios_base::trunc);
    file1.close();
    for(;first1 !=last1;first1++)
    {
        bool adm=first1->get_adm();
        first1->regist(first1->get_login(),first1->get_pass(),adm,first1->get_money());
    }
    return 0;
}
/*!
 * \brief Метод, удаляющий все дома из аккаунта.
 */
void account::delete_all_house()
{
    vector<house>::iterator begin=homes.begin();
    vector<house>::iterator end=homes.end();
    homes.erase(begin,end);
}
/*!
 * \brief Метод, реализующий удаление аккаунта.
 */
void account::home_account()//по просьбе Егора
{
    std::vector<house>::iterator first=homes.begin();
    for(int k=homes.size();k;k--)
    {
        if(login !=first->get_owner())
        {
            homes.erase(first);
        }
        else
        {
            first++;
        }
    }
}
/*!
 * \brief Метод, выключающий девайс.
 * \param a Дом, в котором нужно отключить девайсы.
 * \param i Переменная, отключающая девайсы.
 */
void account::off_devais(house &a,int i){
    vector<house>::iterator iter=find(homes.begin(),homes.end(),a);
    iter->off_devais(i);
    save_all();
}
/*!
 * \brief Метод, реализующий удаление девайса.
 * \param a Дом, в котором нужно удалить девайс.
 * \param exp Комната в доме, в которой нужно отключить девайс.
 * \param dev_ Девайс, который нужно отключить
 */
void account::delete_devais(house &a,const room exp,const devais dev_)
{
    read_all();
    vector<house>::iterator delete_dev=find(homes.begin(),homes.end(),a);
    delete_dev->delete_devais(dev_,exp);
    save_all();
}
/*!
 * \brief Метод, реализующий добавление девайса.
 * \param new_dev Новый девайс, который необходимо добавить.
 * \param a Дом, в который добавляется девайс.
 * \param exp Комната в доме, в которую нужно добавить девайс.
 */
void account::push_devais(devais &new_dev,house &a, const room exp)
{
    read_all();
    vector<house>::iterator push_dev=find(homes.begin(),homes.end(),a);
    push_dev->push_devais(new_dev,exp);
    save_all();
}
/*!
 * \brief Метод, добавляющий деньги, для оплаты.
 * \param b Количество денег, необходимых для оплаты.
 */
void account::add_money(const double b)
{
    money += b;
    std::vector<account> all;
    ifstream file;
    std::string _login;
    std::string _pass;
    int k;
    double m;
    char* str[2];

    file.open("logins.dat",ios_base::binary);
    while(1)
    {
        file.read((char*)&k,sizeof(int));
        str[0]=new char[k+1];
        file.read((char*)str[0],sizeof(char)*k);
        strcat(str[0],"\0");
        if(file.eof())
        {
            delete str[0];
            break;
        }
        file.read((char*)&k,sizeof(int));
        str[1]=new char[k+1];
        file.read((char*)str[1],sizeof(char)*k);
        strcpy(str[1]+k,"\0");
        file.read((char*)&k,sizeof(int));
        file.read((char*)&m,sizeof(double));
        _login=str[0];
        _pass=str[1];
        delete [] str[0];
        delete [] str[1];
        if(login==_login)
        {
            m=money;
        }
        account a(_login,_pass,k,m);
        all.push_back(a);
    }
    file.close();
    auto first=all.begin();
    auto last=all.end();
    ofstream file1;
    file1.open("logins.dat",ios_base::binary | ios_base::trunc);
    file1.close();
    for(;first !=last;first++)
    {
        bool adm=first->get_adm();
        first->regist(first->get_login(),first->get_pass(),adm,first->get_money());
    }
}
/*!
 * \brief Конструктор класса account, инициализирующий логин.
 * \param str Значение логина.
 */
account::account(std::string &str)
{
    login=str;
}
/*!
 * \brief Метод класаа account ,отвечающий за привоение суммы денег.
 * \param a - сумма ,которую присваивают.
 */
void account::put_money(double a)
{
    money=a;
}
