/*!
\file
\brief Исходный файл, содержащий все методы класса room.
*/
#include "room.h"
#include "devais.h"
#include<fstream>
#include <algorithm>
#include <iterator>
using namespace std;
/*!
 * \brief Конструктор по умолчанию класса room.
 */
room::room()
{

}
/*!
 * \brief Метод, возвращающий private переменную area(площадь комнаты).
 * \return Площадь комнаты.
 */
double room::get_area()
{
    return area;
}
/*!
 * \brief Метод, возвращающий private переменную type(тип комнаты).
 * \return Тип комнаты.
 */
int room::get_type()
{
    return type;
}
/*!
 * \brief Метод, возвращающий private переменную temp_sen(кондиционер).
 * \return Переменную кондиционер.
 */
temperature& room::get_temp_sen()
{
    return temp_sen;
}
/*!
 * \brief Метод, записывающий данные о комнате в файл.
 * \param file Cсылка на имя файла,в который будет происходить запись.
 */
void room::save_all_help2(std::ofstream &file)
{
    char r='r';
    int k;
    double temp;
    auto first =dev.begin();
    auto last=dev.end();
    file.write((char*)&r,sizeof(char));
    file.write((char*)&type,sizeof(int));
    file.write((char*)&area,sizeof(double));
    k=(water_sen.get_have()==true)? 1:0;
    file.write((char*)&k,sizeof(int));
    k=(water_sen.get_on()==true)? 1:0;
    file.write((char*)&k,sizeof(int));
    k=(water_sen.get_norm()==true)? 1:0;
    file.write((char*)&k,sizeof(int));
    temp=water_sen.get_proc();
    file.write((char*)&temp,sizeof(double));//Конец 1
    k=(smoke_sen.get_have()==true)? 1:0;
    file.write((char*)&k,sizeof(int));
    k=(smoke_sen.get_on()==true)? 1:0;
    file.write((char*)&k,sizeof(int));
    k=(smoke_sen.get_norm()==true)? 1:0;
    file.write((char*)&k,sizeof(int));
    temp=smoke_sen.get_proc();
    file.write((char*)&temp,sizeof(double));//Конец 2
    k=(temp_sen.get_have()==true)? 1:0;
    file.write((char*)&k,sizeof(int));
    k=(temp_sen.get_on()==true)? 1:0;
    file.write((char*)&k,sizeof(int));
    k=(temp_sen.get_norm()==true)? 1:0;
    file.write((char*)&k,sizeof(int));
    temp=temp_sen.get_temp();
    k=(temp_sen.get_cond_on()==true)?1:0;
    file.write((char*)&k,sizeof(int));
    file.write((char*)&temp,sizeof(double));
    k=(temp_sen.get_cond_have()==true)?1:0;
    file.write((char*)&k,sizeof(int));
    temp=temp_sen.get_electr();
    file.write((char*)&temp,sizeof(double));
    for(;first !=last;first++)
    {
        first->save_all_help3(file);
    }
}
/*!
 * \brief Метод, с помощью которого изменют значения площади комнаты и типа комнаты.
 * \param _type Тип комнаты.
 * \param _area Площадь комнаты.
 */
void room::put_room(int&_type,double&_area)
{
    type=_type;
    area=_area;
}
/*!
 * \brief Метод, возвращающий private переменные типа sencor(датчики).
 * \param type Тип комнаты
 * \return Датчик воды, если type 1.
 *         Датчик дыма.
 */
sencor& room::get_sensor(int type)
{
    if(type ==1)
    {
        return water_sen;
    }
    return smoke_sen;
}
/*!
 * \brief Метод, считывающий из файла данные о комнатах.
 * \param file Ссылка на имя файла, из которого происходит считывание.
 * \return Возвращает символ, определяющий последующее чтение.
 */
char room::read_all_help2(std::ifstream &file)
{
    bool zn[3];
    int k;
    double proc;
    double _electr;
    char ch;

    file.read((char*)&type,sizeof(int));
    file.read((char*)&area,sizeof(double));
    for(int i=0;i<3;i++)
    {
        file.read((char*)&k,sizeof(int));
        zn[i]=(k==1)? true:false;
    }
    file.read((char*)&proc,sizeof(double));
    water_sen.on_off(zn[1]);
    water_sen.put_sencor(zn[0],zn[2],proc);
    for(int i=0;i<3;i++)
    {
        file.read((char*)&k,sizeof(int));
        zn[i]=(k==1)? true:false;
    }
    file.read((char*)&proc,sizeof(double));
    smoke_sen.on_off(zn[1]);
    smoke_sen.put_sencor(zn[0],zn[2],proc);

    for(int i=0;i<3;i++)
    {
        file.read((char*)&k,sizeof(int));
        zn[i]=(k==1)? true:false;
    }
    proc=0;
    temp_sen.on_off(zn[1]);
    temp_sen.put_sencor(zn[0],zn[2],proc);
    file.read((char*)&k,sizeof(int));
    zn[0]=(k==1)? true:false;
    file.read((char*)&proc,sizeof(double));
    file.read((char*)&k,sizeof(int));
    zn[1]=(k==1)? true:false;
    file.read((char*)&_electr,sizeof(double));
    temp_sen.put_temp(zn[0],proc,zn[1]);
    temp_sen.put_kom(1,_electr);
    file.read((char*)&ch,sizeof(char));
    while(ch=='d')
    {
       devais a;
       ch=a.read_all_help3(file);
       dev.push_back(a);
    }
    return ch;
}
/*!
 * \brief Метод, удаляющий девайс из комнаты.
 * \param dev_ Девайс, который нужно удалить.
 */
void room::delete_dev(const devais dev_)
{
    vector<devais>::iterator str=find(dev.begin(),dev.end(),dev_);
    dev.erase(str);
}
/*!
 * \brief Перегрузка оператора присваивания.
 * \param exp Класс, который нужно присвоить.
 * \return Присвоение класса.
 */
bool room::operator==(room exp)
{
    bool zn;
    zn=(type ==exp.get_type() && area==exp.get_area())? true:false;
    return zn;
}
/*!
 * \brief Метод, возвращающий полное названием комнаты.
 * \return Полное название комнаты.
 */
std::string room::this_room()
{
    std::string str;
    std::string str2;
    if (type==1)
    str="Ванная ";
    else if(type==2)
    str="Кухня ";
    else if(type==3)
    str="Жилая комната ";
    str2=to_string(area);
    for(int i=str2.size()-1;str2[i]=='0' || str2[i]==',' ;i--)
    {
        if(str2[i]==',')
        {
            str2.pop_back();
            break;
        }
      str2.pop_back();
    }
    str+=str2+"м^2.";
    return str;
}
/*!
 * \brief Метод, считающий скорость накрутки счетчика электричества в комнате в час.
 * \return Скорость накрутки счетчика электричества в комнате в час.
 */
double room::sum_elektr()
{
    double s=0;
    if (get_temp_sen().get_cond_on() ==true)
    s+=(get_temp_sen()).get_electr();
    for(vector<devais>::iterator iter=dev.begin(); iter!=dev.end();iter++)
    {
        if(iter->get_on()==true)
        s+=iter->get_electr();
    }
    return s;
}
/*!
 * \brief Метод, считающий скорость накрутки счетчика газа в комнате в час.
 * \return Скорость накрутки счетчика газа в комнате в час.
 */
double room::sum_gass()
{
    double s=0;
    for(vector<devais>::iterator iter=dev.begin(); iter!=dev.end();iter++){
        if(iter->get_on()==true)
        s+=iter->get_gas();
    }
    return s;
}
/*!
 * \brief Метод, считающий скорость накрутки счетчика водыв комнате в час.
 * \return Скорость накрутки счетчика воды в комнате в час.
 */
double room::sum_waterr()
{
    double s=0;
    for(vector<devais>::iterator iter=dev.begin(); iter!=dev.end();iter++){
        if(iter->get_on()==true)
        s+=iter->get_water();
    }
    return s;
}
/*!
 * \brief Промежуточный метод для отключения всех девайсов.
 * \param i Сигнал, для отключения.
 */
void room::off_devais(int i){
    if(i==1 && get_temp_sen().get_electr() !=0 && get_temp_sen().get_have() && get_temp_sen().get_on()
            && get_temp_sen().get_cond_have())
    {
        bool k=true;
        bool n=false;
        double a=get_temp_sen().get_temp();
        get_temp_sen().put_temp(n,a,k);
    }
    for(vector<devais>::iterator iter=dev.begin(); iter!=dev.end();iter++){
        switch (i) {
        case 1: if(iter->get_electr()!=0){
                iter->on_off(0);
            }
            break;
        case 2: if(iter->get_gas()!=0){
                iter->on_off(0);
            }
            break;
        case 3: if(iter->get_water()!=0){
                iter->on_off(0);
            }
            break;
        }
    }
}
/*!
 * \brief Метод, добавляющий новый девайс в комнату.
 * \param new_dev Новый девайс, который необходимо добавить.
 */
void room::push_devais(devais &new_dev)
{
    dev.push_back(new_dev);
}
/*!
 * \brief Метод, возвращающий private переменную dev(девайсы, находящиеся в комнате).
 * \return Девайсы, находящиеся в комнате.
 */
std::vector<devais> room::get_dev()
{
    return dev;
}
