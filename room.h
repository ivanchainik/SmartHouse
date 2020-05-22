/*!
/file
/brief Заголовочный файл с описанием класса room.
*/
#ifndef ROOM_H
#define ROOM_H
#include "sencor.h"
#include "devais.h"
#include "temperature.h"
#include <vector>
#include <fstream>
/*!
 * \brief Класс, содержащий все методы для работы с комнатой.Классов наследников не имеет.
 */
class room
{
private:
    int type;///< Тип комнаты.
    sencor water_sen;///< Датчик воды.
    sencor smoke_sen;///< Датчик дыма.
    double area;///< Площадь комнаты.
    temperature temp_sen;///< Кондиционер.
    vector<devais> dev;///< Девайсы, находящиеся в комнате.
public:
    room();
    double get_area();
    int get_type();
    void save_all_help2(ofstream &file);
    void put_room(int&_type,double&_area);
    sencor& get_sensor(int type);    
    char read_all_help2(std::ifstream &file);
    temperature& get_temp_sen();
    void delete_dev(const devais dev_);
    bool operator==(room exp);
    std::string this_room();
    double sum_elektr();
    double sum_gass();
    double sum_waterr();
    void off_devais(int i);
    void push_devais(devais &new_dev);
    std::vector<devais> get_dev();
};


#endif // ROOM_H
