/*!
\file
\brief Исходный файл, содержащий все методы класса counter.
*/
#include "counter.h"
/*!
 * \brief Конструктор по умолчанию класса counter.
 */
counter::counter()
{

}
/*!
 * \brief Метод, возвращающий значение счетчика.
 * \return Значение счетчика.
 */
double counter::get_value()
{
    return value;
}
/*!
 * \brief Метод, с помощью которого можно менять значение private переменных.
 * \param a Новое значение счетчика.
 * \param _on Значение флага работы счетчика.
 * \param _have Наличие счетчика.
 * \param _norm Значение сломан ли счетчик.
 */
void counter::change_sensor(const double &a,const bool &_on,const bool &_have,const bool &_norm)
{
    value=a;
    have=_have;
    on=_on;
    norm=_norm;
}
