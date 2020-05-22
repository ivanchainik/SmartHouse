/*!
\file
\brief Исходный файл, содержащий описание методов класса del_room.
*/
#include "del_room.h"
#include "ui_del_room.h"
#include "account.h"
#include "room.h"

/*!
 * \brief Конструктор класса del_room. Передает значения параметров приватным переменным.
 * \param _user Передает информацию об аккаунте
 * \param _adress Передаёт информации адреса по которому находится комната.
 * \param parent Передаёт указатель на родителя.
 */
del_room::del_room(account &_user,std::string &_adress,mainmenu *parent) :
    QWidget(parent),
    ui(new Ui::del_room)
{
    user=_user;
    user.delete_all_house();
    batya=parent;
    adress=_adress;
    ui->setupUi(this);
    obnova();
    setWindowTitle("\"Умный дом\":Удаление комнаты.");
    QPixmap pix(":/picha/Pichures/del_room.png");
}
/*!
 * \brief Деструктор класса del_room.
 */
del_room::~del_room()
{
    delete ui;
}
/*!
 * \brief Метод возвращающий на предыдущую страницу.
 */
void del_room::on_back_clicked()
{
    batya->obnov(user.get_login(),user.get_pass(),user.get_adm(),user.get_money());
    delete this;
}
/*!
 * \brief Метод обновляющий страницу.
 */
void del_room::obnova()
{
    user.read_all();
    std::vector<house> all=user.get_homes();
    std::vector<house>::iterator first=all.begin();
    std::vector<house>::iterator last=all.end();
    for(;first !=last;first++)
    {
        if(first->full_adress()==adress)
        {
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
            ui->Roomlist->addItem(a);
            ui->Roomlist->setCurrentItem(a);

        }
        else
            ui->Roomlist->addItem(QString::fromStdString(first1->this_room()));
    }
}
/*!
 * \brief Метод отвечающий за удаление комнаты.
 */
void del_room::on_delet_clicked()
{
    std::vector<house> all=user.get_homes();
    std::vector<house>::iterator first=all.begin();
    std::vector<house>::iterator last=all.end();
    for(;first !=last;first++)
    {
        if(first->full_adress()==adress)
        {
            break;
        }
    }
    std::vector<room> allr=first->get_lives();
    if (allr.size()==1)
    {
        ui->warning->setStyleSheet("QLabel {background-color:rgb(204,0,0);color: rgb(238, 238, 236);}");
        ui->warning->setText("\t    Нельзя удалить единственную комнату.");
    }
    else
    {
        std::vector<room>::iterator first1=allr.begin();
        std::vector<room>::iterator last1=allr.end();
        for(;first1 !=last1;first1++)
        {
            if(first1->this_room()==ui->Roomlist->currentItem()->text().toStdString())
            {
                first->delete_room((*first1));
                break;
            }
        }
        user.delete_house(*first);
        user.in_vector(*first);
        user.save_all();
        user.delete_all_house();
        ui->Roomlist->clear();
        obnova();
        ui->warning->setStyleSheet("QLabel {background-color:rgb(32, 180, 28);color: rgb(238, 238, 236);}");
        ui->warning->setText("\t      Комната успешно удалена.");
     }
}
