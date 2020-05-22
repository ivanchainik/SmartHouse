/*!
\file
\brief Заголовочный файл с описанием класса tarif.
  */
#ifndef TARIF_H
#define TARIF_H
#include "account.h"
/*!
 * \brief Класс, содержащий все методы для работы с тарифами. Классов наследников не имеет.
 */
class tarif
{
    double gaz;///< Тариф за газ.
    double water;///< Тариф за воду
    double electr;///< Тариф за электричество.
    int dayofpay;///< День оплаты.
public:
    int get_dayofpay();
    double get_water();
    double get_gaz();
    double get_electr();
    int days_to_pay();
    void showtarif();
    void change_tarif(int type,double value);//тот что не change
    void change_tarif(int day);//тот что не change2
    tarif();
    ~tarif();
};
#endif // TARIF_H
