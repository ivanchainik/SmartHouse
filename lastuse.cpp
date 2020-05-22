/*!
  \file
  \brief Файл,содержащий описания методов класса LastUse.
  */
#include "lastuse.h"
#include <QCoreApplication>
#include <iostream>
#include <fstream>
#include "tarif.h"
#include <ctime>
#include <cstring>

using namespace std;
/*!
 * \brief Конструктор класса LastUse.
 */
LastUse::LastUse()
{

}
/*!
 * \brief Конструктор класса LastUse с параметрами.
 * \param login -имя пользователя.
 * \param ok -Флаг ,показывающий оплату.
 * \param a -Массив ,содержащий значения времени последнего захода.
 */
LastUse::LastUse(string login,bool &ok,int a[])
{
    account _user(login);
    user=_user;
    fl=ok;
    day=a[0];
    month=a[1];
    hour=a[2];
}
/*!
 * \brief Метод класса LastUse ,заполняющий аккаунт.
 * \param _user-аккаунт.
 */
void LastUse::put_account(account &_user)
{
    user=_user;
}
/*!
 * \brief Основной метод класса LastUse.
 */
void LastUse::load()
{
      vector<LastUse> all;
      int k;
      char* str;
      std::string login;
      int a[3];
      bool ok;

      ifstream file("lastouse.dat",ios_base::binary);
      if(!file.is_open())
      {
      }
      else
      {
          while(1)
          {
                file.read((char*)&k,sizeof(int));
                if(file.eof())
                {
                    file.close();
                    break;
                }
                str=new char[k];
                file.read((char*)str,sizeof(char)*k);
                login=str;
                delete[]str;
                file.read((char*)&ok,sizeof(bool));
                file.read((char*)a,sizeof(int)*3);
                LastUse one(login,ok,a);
                all.push_back(one);
          }
      }
      vector<LastUse>::iterator first=all.begin();
      for(;first!=all.end();first++)
      {
            if(user.get_login()==first->get_login())
            {
                first->put_account(user);
                first->oplata();
                break;
            }
      }
      if(first==all.end())
      {
          time_t T;
          struct tm *Time;
          time (&T);
          Time = localtime(&T);
          day=Time->tm_mday;
          month=Time->tm_mon;
          hour=Time->tm_hour;
          fl=false;
          all.push_back(*this);
      }
      ofstream filez("lastouse.dat",ios_base::binary);
      first=all.begin();
      for(;first!=all.end();first++)
      {
            first->save_one(filez);
      }
      filez.close();
}
/*!
 * \brief
 * \return Имя пользователя.
 */
string LastUse::get_login()
{
    return user.get_login();
}
/*!
 * \brief Метод класса LastUse, сохраняющий один экземпляр класса.
 * \param file-файл ,в который идет запись.
 */
void LastUse::save_one(ofstream &file)
{
    int k=user.get_login().size()+1;
    file.write((char*)&k,sizeof(int));
    file.write((char*)user.get_login().c_str(),sizeof(char)*k);
    file.write((char*)&fl,sizeof(bool));
    file.write((char*)&day,sizeof(int));
    file.write((char*)&month,sizeof(int));
    file.write((char*)&hour,sizeof(int));
}
/*!
 * \brief Метод класса LastUse, отвечающий за удаление аккаунта.
 */
void LastUse::dell_acc()
{
    vector<LastUse> all;
    int k;
    char* str;
    std::string login;
    int a[3];
    bool ok;

    ifstream file("lastouse.dat",ios_base::binary);

        while(1)
        {
              file.read((char*)&k,sizeof(int));
              if(file.eof())
              {
                  file.close();
                  break;
              }
              str=new char[k];
              file.read((char*)str,sizeof(char)*k);
              login=str;
              delete[]str;
              file.read((char*)&ok,sizeof(bool));
              file.read((char*)a,sizeof(int)*3);
              LastUse one(login,ok,a);
              all.push_back(one);
        }
    vector<LastUse>::iterator first=all.begin();
    for(;;first++)
    {
          if(user.get_login()==first->get_login())
          {
              all.erase(first);
              break;
          }
    }
    ofstream filez("lastouse.dat",ios_base::binary);
    first=all.begin();
    for(;first!=all.end();first++)
    {
          first->save_one(filez);
    }
    filez.close();
}
/*!
 * \brief Метод класса LastUse, отвечающий за оплату.
 */
void LastUse::oplata()
{
        int raz;
        time_t T;
        struct tm *Time;
        time (&T);
        Time = localtime(&T);
        double a;
        tarif tar;

        if(month<Time->tm_mon)
        {
            raz=(12-month+Time->tm_mon)*30*24;
        }
        else
        {
            raz=(month-Time->tm_mon)*30*24;
        }
        raz+=(Time->tm_mday-day)*24;
        raz+=(Time->tm_hour-hour);
        user.read_all();
        vector<house> all=user.get_homes();
        for(vector<house>::iterator first=all.begin();first !=all.end();first++)
        {
            if(first->get_owner()==user.get_login())
            {
                bool k[3];
                k[0]=first->get_sencor(1).get_have();
                k[1]=first->get_sencor(1).get_on();
                k[2]=first->get_sencor(1).get_norm();
                a=first->get_sencor(1).get_value()+raz*first->sum_electr();
                first->get_sencor(1).change_sensor(a,k[1],k[0],k[2]);
                k[0]=first->get_sencor(2).get_have();
                k[1]=first->get_sencor(2).get_on();
                k[2]=first->get_sencor(2).get_norm();
                a=first->get_sencor(2).get_value()+raz*first->sum_gas();
                first->get_sencor(2).change_sensor(a,k[1],k[0],k[2]);
                k[0]=first->get_sencor(3).get_have();
                k[1]=first->get_sencor(3).get_on();
                k[2]=first->get_sencor(3).get_norm();
                a=first->get_sencor(3).get_value()+raz*first->sum_water();
                first->get_sencor(3).change_sensor(a,k[1],k[0],k[2]);
                user.delete_house(*first);
                user.in_vector(*first);
            }
        }
        if((tar.days_to_pay()==0 && month==Time->tm_mon && fl==false) ||(Time->tm_mon-month !=month && fl==false)\
                || (Time->tm_mday>tar.get_dayofpay() && Time->tm_mon==month && fl==false))
        {
            fl=true;
            double sum=0;
            for(vector<house>::iterator first=all.begin();first !=all.end();first++)
            {
                if(first->get_owner()==user.get_login())
                {
                    a=0;
                    bool k[3];
                    double t[6];
                    t[0]=first->get_sencor(1).get_value();
                    t[1]=t[0]*tar.get_electr();
                    t[2]=first->get_sencor(2).get_value();
                    t[3]=t[2]*tar.get_gaz();
                    t[4]=first->get_sencor(3).get_value();
                    t[5]=t[4]*tar.get_water();
                    first->last_coun(t);
                    k[0]=first->get_sencor(1).get_have();
                    k[1]=first->get_sencor(1).get_on();
                    k[2]=first->get_sencor(1).get_norm();
                    sum=first->get_sencor(1).get_value()*tar.get_electr();
                    first->get_sencor(1).change_sensor(a,k[1],k[0],k[2]);
                    k[0]=first->get_sencor(2).get_have();
                    k[1]=first->get_sencor(2).get_on();
                    k[2]=first->get_sencor(2).get_norm();
                    sum+=first->get_sencor(2).get_value()*tar.get_gaz();
                    first->get_sencor(2).change_sensor(a,k[1],k[0],k[2]);
                    k[0]=first->get_sencor(3).get_have();
                    k[1]=first->get_sencor(3).get_on();
                    k[2]=first->get_sencor(3).get_norm();
                    sum+=first->get_sencor(3).get_value()*tar.get_water();
                    first->get_sencor(3).change_sensor(a,k[1],k[0],k[2]);
                    sum=-sum;
                    user.delete_house(*first);
                    user.in_vector(*first);
                    user.add_money(sum);
                }
            }
        }
        user.save_all();
        user.delete_all_house();
        day=Time->tm_mday;
        month=Time->tm_mon;
        hour=Time->tm_hour;
}
/*!
 * \brief Метод класса LastUse, возвращающий деньги пользователя.
 * \return Кол-во денег у пользователя.
 */
double LastUse::get_money()
{
    return user.get_money();
}
