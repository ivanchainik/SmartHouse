/*!
  \file
  \brief Исходный файл, содержащий все методы класса temperature.
*/
#include "temperature.h"

/*!
 * \brief Конструктор поумолчанию.
 */
temperature::temperature()
{

}
/*!
 * \brief Метод возвращающий значение температуры.
 * \return Значение температуры.
 */
double temperature::get_temp()
{
    return temp;
}
/*!
 * \brief Метод возвращающи значение состояния On/Off.
 * \return On/Off.
 */
bool temperature::get_cond_on()
{
    return cond_on;
}
/*!
 * \brief Метод позволяющий поменять значения являющиеся приватными.
 * \param _cond Параметр передащий значение состояния On/Off.
 * \param _temp Параметр передащий значение температуры.
 * \param _have Параметр передащий значение наличия.
 */
void temperature::put_temp(bool &_cond, double &_temp,bool & _have)
{
    cond_have=_have;
    cond_on=_cond;
    temp=_temp;
}
/*!
 * \brief Метод возвращающий значение наличия.
 * \return Есть/Отсутствует.
 */
bool temperature::get_cond_have()
{
    return cond_have;
}

