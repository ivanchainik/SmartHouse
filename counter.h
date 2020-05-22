/*!
\file
\brief Заголовочный файл с описанием класса counter.
*/
#ifndef COUNTER_H
#define COUNTER_H
#include "sencor.h"
/*!
 * \brief Класс, содержащий все методы для работы со счетчиками. Является классом наследником класса sencor.
 */
class counter : public sencor {
private:
    double value;///< Значение счетчика.
public:
    counter();
    double get_value();
    void change_sensor(const double &a,const bool &_on,const bool &_have,const bool &_norm);
};

#endif // COUNTER_H
