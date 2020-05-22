/*!
\file
\brief Исходный файл, содержащий все методы класса devais.
*/
#include "devais.h"
#include<cstring>
/*!
 * \brief Конструктор по умолчанию класса devais.
 */
devais::devais()
{

}
/*!
 * \brief Метод, возвращающий private переменную name(имя девайса).
 * \return Имя девайса.
 */
string devais::get_name()
{
    return name;
}
/*!
 * \brief Метод, возвращающий protected переменную on(флаг работы девайса).
 * \return Флаг работы девайса.
 */
bool devais::get_on()
{
    return on;
}
/*!
 * \brief Метод, записывающий данные о девайсе в файл.
 * \param file Ссылка на имя файла, в который происходит запись.
 */
void devais::save_all_help3(ofstream &file)
{
    char d='d';
    int k;
    file.write((char*)&d,sizeof(char));
    k=name.size();
    file.write((char*)&k,sizeof(int));
    file.write((char*)name.c_str(),sizeof(char)*k);
    k=(on==true)?1:0;
    file.write((char*)&k,sizeof(int));
    file.write((char*)&electr,sizeof(double));
    file.write((char*)&water,sizeof(double));
    file.write((char*)&gas,sizeof(double));
}
/*!
 * \brief Метод, с помощью которого изменяют имя девайса.
 * \param _name Новое имя девайса.
 */
void devais::put_devais(std::string &_name)
{
    name=_name;
}
/*!
 * \brief Метод, с помощью которого меняют флаг работы девайса.
 * \param _on Значение флага работы девайса.
 */
void devais::on_off(bool _on)
{
    on=_on;
}
/*!
 * \brief Метод, возвращающий private переменную electr(количество потребляемой электроэнергии).
 * \return Количество потребляемой электроэнергии.
 */
double devais::get_electr()
{
    return electr;
}
/*!
 * \brief Метод, возвращающий private переменную gas(количество потребляемого газа).
 * \return Количество потребляемого газа.
 */
double devais::get_gas()
{
    return gas;
}
/*!
 * \brief Метод, возвращающий private переменную water(количество потребляемой воды).
 * \return Количество потребляемой воды.
 */
double devais::get_water()
{
    return water;
}
/*!
 * \brief Метод, считывающий из файла данные о девайсе.
 * \param file Ссылка на имя файла, из которого происходит считывание.
 * \return Возвращает символ, определяющий следующие чтение.
 */
char devais::read_all_help3(ifstream &file)
{
    int k;
    char *str;
    char ch;
    file.read((char*)&k,sizeof(int));
    str=new char[k+1];
    file.read((char*)str,sizeof(char)*k);
    strcpy(str+k,"\0");
    name=str;
    delete []str;
    file.read((char*)&k,sizeof(int));
    on=(k==1)? true:false;
    file.read((char*)&electr,sizeof(double));
    file.read((char*)&water,sizeof(double));
    file.read((char*)&gas,sizeof(double));
    file.read((char*)&ch,sizeof(char));
    return ch;
}
/*!
 * \brief Перегрузка оператора присваивания.
 * \param dev_ Класс к которому присваивают.
 * \return Способ присваивания.
 */
bool devais::operator==(devais dev_)
{
    return (name==dev_.get_name())?true:false;
}
/*!
 * \brief Метод,заполняющий потребление ресурсов.
 * \param type Тип ресурса.
 * \param zn Количество потребления.
 */
void devais::put_kom(int type,const double &zn)
{
    if(type==1)
    {
        electr=zn;
    }
    else if(type==2)
    {
        gas=zn;
    }
    else
    {
        water=zn;
    }
}
