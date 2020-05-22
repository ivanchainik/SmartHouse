/*!
\file
\brief Исходный файл, содеражащий все методы класса tarif.
  */
#include <iostream>
#include <cstdio>
#include "tarif.h"
#include <fstream>
#include <ctime>
/*!
 * \brief Метод, возвращающий private переменную dayofpay(день оплаты).
 * \return День оплаты.
 */
int tarif::get_dayofpay(){
   return dayofpay;
}
/*!
 * \brief Метод, возвращающий private переменную gaz(тариф за газ).
 * \return Тариф за газ.
 */
double tarif::get_gaz(){
   return gaz;
}
/*!
 * \brief Метод, возвращающий private переменную water(тариф за воду).
 * \return Тариф за воду.
 */
double tarif::get_water(){
   return water;
}
/*!
 * \brief Метод, возвращающий private переменную electr(тариф за электричество).
 * \return Тариф за электричество.
 */
double tarif::get_electr(){
   return electr;
}
/*!
 * \brief Метод, изменяющий тарифы.
 * \param type Перменная для выбора тарифа.
 * \param value Новое значение тарифа.
 */
void tarif::change_tarif(int type,double value){
    switch (type) {
        case 1:{
            gaz=value;
                break;
        }
        case 2:{
           water=value;
            break;
        }
        case 3:{
            electr=value;
            break;
        }
    }
}
/*!
 * \brief Метод, изменяющий день оплаты.
 * \param day Новый день оплаты.
 */
void tarif::change_tarif(int day){
    dayofpay=day;
}
/*!
 * \brief Конструктор класса тариф, считывающий данные из файла.
 */
tarif::tarif(){
    std::ifstream tarifs;
    tarifs.open("tarifs.dat",std::ios_base::binary);
    if (tarifs.is_open()){
        tarifs.read((char*)&dayofpay,sizeof (int));
        tarifs.read((char*)&gaz,sizeof (double));
        tarifs.read((char*)&water,sizeof (double));
        tarifs.read((char*)&electr,sizeof (double));
        tarifs.close();
    }
    else
    {
        dayofpay=1;
        gaz=0;
        water=0;
        electr=0;
    }
}
/*!
 * \brief Деструктор класса tarif, записывающий данные из класса в файл.
 */
tarif::~tarif(){
    std::ofstream tarifs;
    tarifs.open("tarifs.dat",std::ios_base::binary);
    tarifs.write((char*)&dayofpay,sizeof (int));
    tarifs.write((char*)&gaz,sizeof (double));
    tarifs.write((char*)&water,sizeof (double));
    tarifs.write((char*)&electr,sizeof (double));
    tarifs.close();}
/*!
 * \brief Метод, возвращающий количество дней до оплаты.
 * \return Количество дней до оплаты.
 */
int tarif::days_to_pay()
{
    time_t T;
    struct tm *Time;
    time (&T);
    Time = localtime(&T);
    int Thedayofpay = dayofpay;
    int Dayinmonth = 31;
    if (Time->tm_mon == 1)
    {
        if ((Time->tm_year % 4) == 0)
        {
            Dayinmonth = 29;
            if (Thedayofpay > 29) {Thedayofpay = 29;}
        }
        else
        {
            Dayinmonth = 28;
            if (Thedayofpay > 28) {Thedayofpay = 28;}
        }
    }
    if ((Time->tm_mon == 3) || (Time->tm_mon == 5) || (Time->tm_mon == 8) || (Time->tm_mon == 10))
    {
        Dayinmonth = 30;
        if (Thedayofpay > 30) {Thedayofpay = 30;}
    }
    if (Time->tm_mday <= Thedayofpay)
        {return (Thedayofpay - Time->tm_mday);}
     else
        {return (Dayinmonth - Time->tm_mday + Thedayofpay);}
}
