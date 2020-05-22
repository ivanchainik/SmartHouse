/*!
\file
\brief Исходный файл с описанием методов класса chang_room.
*/
#include "chang_room.h"
#include "ui_chang_room.h"
#include "account.h"
/*!
 * \brief Конструктор класса chang_room.
 * \param auser Аккаунт, в котором происходит изменение.
 * \param _adress Адресс дома, в котором находится комната.
 * \param parent Указатель на класс родитель
 */
Chang_room::Chang_room(const account &auser,std::string &_adress,mainmenu *parent) :
    QWidget(parent),
    ui(new Ui::Chang_room)
{
    ui->setupUi(this);
    user=auser;
    par=parent;
    adress=_adress;
    obnova();
    setWindowTitle("\"Умный дом\":Изменение комнаты.");
    QPixmap pix(":/picha/Pichures/chang_room.png");
}
/*!
 * \brief Деструктор класса chang_room.
 */
Chang_room::~Chang_room()
{
    delete ui;
}
/*!
 * \brief Метод класса chanf_room, отвечающий за обновление окна.
 */
void Chang_room::obnova()
{
    ui->rooms->clear();
    user.delete_all_house();
    user.read_all();
    std::vector<house> all=user.get_homes();
    std::vector<house>::iterator first=all.begin();
    std::vector<house>::iterator last=all.end();
    for(;first !=last;first++)
    {
        if(first->full_adress()==adress)
        {
             home=*first;
            break;
        }
    }
    std::vector<room> allr=first->get_lives();
    std::vector<room>::iterator first1=allr.begin();
    std::vector<room>::iterator last1=allr.end();
    for(;first1 !=last1;first1++)
    {
        if(first1==allr.begin())
        {
            QListWidgetItem *a=new  QListWidgetItem(QString::fromStdString(first1->this_room()));
            ui->rooms->addItem(a);
            ui->rooms->setCurrentItem(a);
        }
        else
            ui->rooms->addItem(QString::fromStdString(first1->this_room()));
    }
}
/*!
 * \brief Метод класса chang_room, отвечающий за обновлении окна при выборе комнаты.
 */
void Chang_room::on_rooms_itemSelectionChanged()
{
    std::vector<room> allr=home.get_lives();
    std::vector<room>::iterator first1=allr.begin();
    std::vector<room>::iterator last1=allr.end();
    for(;first1 !=last1;first1++)
    {
        if(first1->this_room()==ui->rooms->currentItem()->text().toStdString())
        {
            if(first1->get_type()==1)
            {
                ui->bath_type->setChecked(true);
            }
            else if(first1->get_type()==2)
            {
                ui->kitch_type->setChecked(true);
            }
            else
            {
                ui->Liv_type->setChecked(true);
            }
            ui->arealine->setText(QString("%1").arg(first1->get_area()));
        }
    }
    ui->warning->setStyleSheet("QLabel {background-color: rgba(204, 0, 0,1)");
    ui->warning->clear();
}
/*!
 * \brief Метод класса chang_room, отвечающий за редактирование комнаты.
 */
void Chang_room::on_Enter_clicked()
{
    bool ok;
    double _area;
    _area=ui->arealine->text().toDouble(&ok);
    if(ok !=true)
    {
            ui->warning->setStyleSheet("QLabel {background-color: rgb(204, 0, 0);color: rgb(238, 238, 236);}");
            ui->warning->setText("\t               Требовалось ввести число.");
            return;
    }
    else if(_area<=0)
    {
            ui->warning->setStyleSheet("QLabel {background-color: rgb(204, 0, 0);color: rgb(238, 238, 236);}");
            ui->warning->setText("\tПлощадь комнаты долна быть больше нуля.");
            return;
    }
    std::vector<room> allr=home.get_lives();
    std::vector<room>::iterator first1=allr.begin();
    std::vector<room>::iterator last1=allr.end();
    for(;first1 !=last1;first1++)
    {
           if(first1->this_room()==ui->rooms->currentItem()->text().toStdString())
                {
                    home.delete_room(*first1);
                    room a;
                    int k;
                    if(ui->bath_type->isChecked())
                    k=1;
                    else if(ui->kitch_type->isChecked())
                    k=2;
                    else
                    k=3;
                    a.put_room(k,_area);
                    home.in_vector(a);
                }
    }
    user.delete_house(home);
    user.in_vector(home);
    user.save_all();
    obnova();
    par->obnov(user.get_login(),user.get_pass(),user.get_adm(),user.get_money());
    ui->warning->setStyleSheet("QLabel {background-color:rgb(32, 180, 28);color: rgb(238, 238, 236);}");
    ui->warning->setText("\t            Изменения успешны.");
}
/*!
 * \brief Метод класа chang_room, отвечающий за выход из окна.
 */
void Chang_room::on_back_clicked()
{
    delete this;
}
