/*!
\file
\brief Исходный файл, содержащий все методы класса house.
*/
#include "house.h"
#include <cstring>
#include <iterator>
#include <algorithm>
/*!
 * \brief Конструктор по умолчанию.
 */
house::house()
{

}
/*!
 * \brief Метод, возвращающий private переменную flat(номер квартры).
 * \return Номер квартиры.
 */
int house::get_flat()
{
    return flat;
}
/*!
 * \brief Метод, возвращающий private переменную street(улица).
 * \return Улицу.
 */
string house::get_street()
{
    return street;
}
/*!
 * \brief Метод, возвращающий private переменную owner(владелец).
 * \return Владелец.
 */
string house::get_owner()
{
    return owner;
}
/*!
 * \brief Метод, записывающий данные о доме в файл.
 * \param file Ссылка на имя файла, в который происходит запись.
 */
void house::save_all_help(ofstream &file)
{
    int k;
    double z;
    auto first=lives.begin();
    auto last=lives.end();
    k=(tarelectr.get_have()==true)? 1:0;
    file.write((char*)&k,sizeof(int));
    k=(tarelectr.get_on()==true)? 1:0;
    file.write((char*)&k,sizeof(int));
    k=(tarelectr.get_norm()==true)? 1:0;
    file.write((char*)&k,sizeof(int));
    z=tarelectr.get_value();
    file.write((char*)&z,sizeof(double));//Конец 1.
    k=(targaz.get_have()==true)? 1:0;
    file.write((char*)&k,sizeof(int));
    k=(targaz.get_on()==true)? 1:0;
    file.write((char*)&k,sizeof(int));
    k=(targaz.get_norm()==true)? 1:0;
    file.write((char*)&k,sizeof(int));
    z=targaz.get_value();
    file.write((char*)&z,sizeof(double));//Конец 2.
    k=(tarwater.get_have()==true)? 1:0;
    file.write((char*)&k,sizeof(int));
    k=(tarwater.get_on()==true)? 1:0;
    file.write((char*)&k,sizeof(int));
    k=(tarwater.get_norm()==true)? 1:0;
    file.write((char*)&k,sizeof(int));
    z=tarwater.get_value();
    file.write((char*)&z,sizeof(double));//Конец 3.
    file.write((char*)l_electr,sizeof(double)*2);
    file.write((char*)l_gas,sizeof(double)*2);
    file.write((char*)l_water,sizeof(double)*2);
    for(;first !=last;first++)
    {
        first->save_all_help2(file);
    }
}
/*!
 * \brief Метод, с помощью которого можно менять значение private переменных.
 * \param _flat Новый номер квартиры.
 * \param _street Новое название улицы.
 * \param _owner Новый владелец.
 * \param _num_house Новый номер дома.
 */
void house::put_house(int&_flat,std::string &_street,std::string &_owner,const int &_num_house)
{
    flat=_flat;
    street=_street;
    owner=_owner;
    num_house=_num_house;
}
/*!
 * \brief Метод, возвращающий private переменную num_house(номер дома).
 * \return Номер дома.
 */
int house::get_num()
{
    return num_house;
}
/*!
 * \brief Метод, создающий новые счетчики.
 * \param a Включение счетчика воды.
 * \param b Включение счетчика электричестваю
 * \param c Включение счетчика газа.
 */
void house::new_couters(const bool &a, const bool &b, const bool &c)
{
        tarwater.change_sensor(0,true,a,true);
        tarelectr.change_sensor(0,true,b,true);
        targaz.change_sensor(0,true,c,true);
}
/*!
 * \brief Метод, добавляющий новую комнату.
 * \param a Новая комната, которую необходимо добавить.
 */
void house::in_vector(room &a)
{
    lives.push_back(a);
}
/*!
 * \brief Метод, считывающий из файла данные о доме.
 * \param file Ссылка на имя файла, из которого происходит считывание.
 */
void house::read_all_help(ifstream &file)
{
    int k;
    char *str;
    bool zn[3];
    double value;
    char ch;

    file.read((char*)&k,sizeof(int));
    str=new char[k+1];
    file.read((char*)str,sizeof(char)*k);
    strcpy(str+k,"\0");
    owner=str;
    delete []str;
    file.read((char*)&k,sizeof(int));
    str=new char[k+1];
    file.read((char*)str,sizeof(char)*k);
    strcpy(str+k,"\0");
    street=str;
    delete []str;
    file.read((char*)&num_house,sizeof(int));
    file.read((char*)&flat,sizeof(int));
    for(int i=0;i<3;i++)
    {
        file.read((char*)&k,sizeof(int));
        zn[i]=(k==1)? true:false;
    }
    file.read((char*)&value,sizeof(double));
    tarelectr.change_sensor(value,zn[1],zn[0],zn[2]);
    for(int i=0;i<3;i++)
    {
        file.read((char*)&k,sizeof(int));
        zn[i]=(k==1)? true:false;
    }
    file.read((char*)&value,sizeof(double));
    targaz.change_sensor(value,zn[1],zn[0],zn[2]);
    for(int i=0;i<3;i++)
    {
        file.read((char*)&k,sizeof(int));
        zn[i]=(k==1)? true:false;
    }
    file.read((char*)&value,sizeof(double));
    tarwater.change_sensor(value,zn[1],zn[0],zn[2]);
    file.read((char*)l_electr,sizeof(double)*2);
    file.read((char*)l_gas,sizeof(double)*2);
    file.read((char*)l_water,sizeof(double)*2);
    file.read((char*)&ch,sizeof(char));
    while(1)
    {
        room a;
        if(a.read_all_help2(file)!='r')
        {
            this->in_vector(a);
            break;
        }
        this->in_vector(a);
    }
}
/*!
 * \brief Перегрузка оператора присваивания.
 * \param a Класс,по которому присваивают.
 * \return Способ присваивания к классу.
 */
bool house::operator==(house a)
{
   return (owner==a.get_owner() && flat==a.get_flat() && num_house==a.get_num())? true:false;
}
/*!
 * \brief Метод, возвращающий полный адресс.
 * \return Полный адресс.
 */
std::string house::full_adress()
{
    std::string str;
    str="Ул.:"+street+" д.:"+std::to_string(num_house)+" кв.:"+std::to_string(flat);
    return str;
}
/*!
 * \brief Метод, удаляющий комнату из дома.
 * \param exp Дом, который нужно удалить.
 */
void house::delete_room(const room exp)
{
    vector<room>::iterator del=find(lives.begin(),lives.end(),exp);
    lives.erase(del);
}
/*!
 * \brief Метод, возвращающий private переменную lives(комнаты в доме).
 * \return Комнаты, находящиеся в доме.
 */
std::vector<room> house::get_lives()
{
    return lives;
}
/*!
 * \brief Метод, возвращающий всю площадь дома.
 * \return Всю площадь дома.
 */
double house::all_area()
{
    double area=0;
    std::vector<room>::iterator first=lives.begin();
    std::vector<room>::iterator last=lives.end();
    for(;first != last;first++)
    {
        area+=first->get_area();
    }
    return area;
}
/*!
 * \brief Метод, считающий скорость накрутки счетчика электричества в доме в час.
 * \return Скорость накрутки счетчика электричества в доме в час.
 */
double house::sum_electr()
{
    double s=0;
    for(vector<room>::iterator iter=lives.begin(); iter!=lives.end();iter++)
    {
        s+=iter->sum_elektr();
    }
    return s;
}
/*!
 * \brief Метод, считывающий скорость накрутки счетчика газа в доме в час.
 * \return Скорость накрутки счетчтка газа в доме в час.
 */
double house::sum_gas()
{
    double s=0;
    for(vector<room>::iterator iter=lives.begin(); iter!=lives.end();iter++)
    {
        s+=iter->sum_gass();
    }
    return s;
}
/*!
 * \brief Метод, считающий скорость накрутки счетчика воды в доме в час.
 * \return Скорость накрутки счетчика воды в доме в час.
 */
double house::sum_water()
{
    double s=0;
    for(vector<room>::iterator iter=lives.begin(); iter!=lives.end();iter++)
    {
        s+=iter->sum_waterr();
    }
    return s;
}
/*!
 * \brief Метод, возвращающий private переменные типа counter(счетчики электричества, газа, воды)
 * \param type Тип счетчика, который надо вернуть.
 * \return Счетчик электричества, если type 1.
 *         Счетчик газа, если type 2.
 *         Счетчик воды, если type не 1 и не 2.
 */
counter& house:: get_sencor(int type)
{
    if(type==1)
        return tarelectr;
    else if(type==2)
        return targaz;
    else
    return tarwater;
}
/*!
 * \brief Промежуточный метод, отключающий все девайсы.
 * \param i Сигнал для отключения девайсов.
 */
void house::off_devais(int i){
    for(vector<room>::iterator iter=lives.begin(); iter!=lives.end();iter++){
        iter->off_devais(i);
    }
}
/*!
 * \brief Промежуточный метод,реализующий, удаление девайса из аккаунта.
 * \param dev_ Девайс, который нужно удалить.
 * \param exp Комната, из которой нужно удалить девайс.
 */
void house::delete_devais(const devais dev_, const room exp)
{
    vector<room>::iterator delete_dev=find(lives.begin(),lives.end(),exp);
    delete_dev->delete_dev(dev_);
}
/*!
 * \brief Промежуточный метод, реализующий добавление девайса в аккаунте.
 * \param new_dev Девайс, который необходимо добавить.
 * \param exp Комната. в которую необходимо добавить девайс.
 */
void house::push_devais(devais &new_dev,const room exp)
{
    vector<room>::iterator push_dev=find(lives.begin(),lives.end(),exp);
    push_dev->push_devais(new_dev);
}
void house::last_coun(double r[])
{
    l_electr[0]=r[0];
    l_electr[1]=r[1];
    l_gas[0]=r[2];
    l_gas[1]=r[3];
    l_water[0]=r[4];
    l_water[1]=r[5];
}
double house::get_last_val(int type,int tar)
{
       if(type==1 && tar==1)
            return l_electr[0];
       else if(type==1 && tar==2)
           return l_electr[1];
       else if(type==2 && tar==1)
           return l_water[0];
       else if(type==2 && tar==2)
           return l_water[1];
       else if(type==3 && tar==1)
           return l_gas[0];
       else if(type==3 && tar==2)
           return l_gas[1];
}
