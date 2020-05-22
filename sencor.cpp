/*!
\file
\brief Исходный файл, содержащий все методы класса sencor.
*/
#include "sencor.h"
/*!
 * \brief Конструктор по умолчанию класса sencor.
 */
sencor::sencor()
{

}
/*!
 * \brief Метод, возвращающий private переменную norm(флаг работы сенсора).
 * \return Флаг работы сенсора.
 */
bool sencor::get_norm()
{
    return norm;
}
/*!
 * \brief Метод, возвращающий private переменную have(флаг наличия сеснора).
 * \return Флаг наличия сенсора.
 */
bool sencor::get_have()
{
    return have;
}
/*!
 * \brief Метод, с помощью которого меняется значение private перемнных класса sencor.
 * \param _have Значение флага наличия сенсора.
 * \param _norm Значение флага работы сенсора.
 * \param _proc Значение процента влияния на сенсоры.
 */
void sencor::put_sencor(bool &_have, bool &_norm,double &_proc)
{
    have=_have;
    norm=_norm;
    proc=_proc;
}
/*!
 * \brief Метод, возвращающий private переменную proc(процент влияния на сенсоры).
 * \return Процент влияния на сенсоры.
 */
double sencor::get_proc()
{
    return proc;
}
