/*!
\file
\brief Заголовочный файл с описание класса devais.
  */
#ifndef DEVAIS_H
#define DEVAIS_H
#include <string>
#include <iostream>
#include<fstream>
using namespace std;
/*!
 * \brief Класс, содержащий все методы для работы с девайсами. Имеет класс наследник sencor.
 */
class devais
{
private:
    string name;///< Название девайса.
    double electr;///< Количество потребляемой электроэнергии.
    double gas;///< Количество потребляемого газа.
    double water;///< Количество потребляемой воды.
protected:
    bool on;///< Флаг работы девайса.
public:
    string get_name();
    bool get_on();
    devais();
    void save_all_help3(ofstream &file);
    void put_devais(std::string &_name);
    void on_off(bool _on);
    double get_electr();
    double get_gas();
    double get_water();
    char read_all_help3(ifstream &file);
    bool operator==(devais dev_);
    void put_kom(int type,const double &zn);
};

#endif // DEVAIS_H
