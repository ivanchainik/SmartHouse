/*!
  \file
  \brief Заголовочный файл с описанием класса.

  Данный файл содержит описание класса temperature.
*/
#ifndef TEMPERATURE_H
#define TEMPERATURE_H
#include "sencor.h"

/*!
 * \brief Класс-наследник класса sensor.
 *
 * Включает в себя все методы работы с кондиционером. Наследников не имеет.
 */
class temperature : public sencor {
private:
     bool cond_on;
     double temp;
     bool cond_have;
public:
    temperature();
    double get_temp();
    bool get_cond_on();
    void put_temp(bool & _cond,double &_temp,bool & cond_have);
    bool get_cond_have();
};

#endif // TEMPERATURE_H
