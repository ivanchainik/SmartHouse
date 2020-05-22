/*!
\file
\brief Заголовочный файл, с описанием класса sencor.
  */
#ifndef SENCOR_H
#define SENCOR_H
#include "devais.h"
/*!
 * \brief Класс, содержащий все методы для работы с сенсорами. Является классом наследником класса devais. Имеет класс наследник temperature,counter.
 */
class sencor : public devais {
private:
    double proc; ///< Процент влияния на сенсоры.
protected:
    bool have; ///< Флаг наличия сенсоров.
    bool norm; ///< Флаг работы сенсора.
public:
    sencor();
    bool get_norm();
    bool get_have();
    void put_sencor(bool &_have,bool &_norm,double &_proc);
    double get_proc();
};

#endif // SENCOR_H
