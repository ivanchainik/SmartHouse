/*!
\file
\brief Заголовочный файл с описанием класса house.
*/
#ifndef HOUSE_H
#define HOUSE_H
#include <string>
#include <vector>
#include "counter.h"
#include <fstream>
#include "room.h"
using namespace std;
/*!
 * \brief Класс, содержащий все методы для работы с домом.
 */
class house
{
private:
    vector<room> lives;///< Комнаты, находящиеся в доме.
    counter tarelectr;///< Счетчик по электричеству.
    counter targaz;///< Счетчик по газу.
    counter tarwater;///< Счетчик по воде.
    int flat;///< Номер квартиры
    int num_house;///< Номер дома.
    string street;///< Улица.
    string owner;///< Владелец.
    double l_electr[2];
    double l_gas[2];
    double l_water[2];
public:
    int get_flat();
    string get_street();
    string get_owner();
    house();
    void save_all_help(ofstream &file);
    void put_house(int&_flat,std::string &_street,std::string &_owner,const int &_num_house);
    int get_num();
    void new_couters(const bool &a,const bool &b,const bool &c);
    void in_vector(room &a);
    void read_all_help(ifstream &file);
    bool operator==(house a);
    std::string full_adress();
    void delete_room(const room exp);
    std::vector<room> get_lives();
    double all_area();
    double sum_electr();
    double sum_gas();
    double sum_water();
    counter& get_sencor(int type);
    void off_devais(int i);
    void delete_devais(const devais dev_, const room exp);
    void push_devais(devais &new_dev,const room exp);
    void last_coun(double r[]);
    double get_last_val(int type,int tar);
};

#endif // HOUSE_H
