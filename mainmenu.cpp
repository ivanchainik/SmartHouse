/*!
  \brief Файл, содержащий описание методов класса mainmenu.
  */
#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "menu.h"
#include "account.h"
#include "tarif.h"
#include "show_tarif.h"
#include "change_tarife.h"
#include "change_pass.h"
#include "give_admin.h"
#include "add_house.h"
#include <vector>
#include <QMessageBox>
#include "add_room.h"
#include "info_house_o.h"
#include "del_room.h"
#include "chang_house.h"
#include "chang_room.h"
#include "work_counter.h"
#include "work_dev.h"
#include "work_sen.h"
#include "money.h"
#include "lastuse.h"
/*!
 * \brief Конструктор класса maimmenu.
 * \param _login-Имя пользователя.
 * \param _pass-Пароль.
 * \param _adm-Флаг администратора.
 * \param _money-Кол-во денег.
 * \param parent-Указатель на родительский класс.
 */
mainmenu::mainmenu(const std::string &_login,const std::string &_pass,const bool &_adm,const double &_money,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainmenu)
{
    ui->setupUi(this);
    obnov(_login,_pass,_adm,_money);
    setWindowTitle("\"Умный дом\":Главное меню.");
}
/*!
 * \brief Деструктор класса mainmenu.
 */
mainmenu::~mainmenu()
{
    delete ui;
}
/*!
 * \brief Метод класса mainmenu,отвечающий за выход к окну регистрации.
 */
void mainmenu::on_pushButton_clicked()
{
    menu *w=new menu;
    delete this;
    w->show();
}
/*!
 * \brief Метод класса mainmenu,отвечающий за открытия окна с информацией о тарифах.
 */
void mainmenu::on_pushButton_2_clicked()
{
    show_tarif *a=new show_tarif(this);
    a->setWindowFlag(Qt::Dialog);
    a->setWindowModality(Qt::WindowModal);
    a->show();

}
/*!
 * \brief Метод класса mainmenu,отвечающий за открытие окна редактирования тарифов.
 */
void mainmenu::on_Changetar_clicked()
{
    change_tarife *a=new change_tarife(this);
    a->setWindowFlag(Qt::Dialog);
    a->setWindowModality(Qt::WindowModal);
    a->show();
}
/*!
 * \brief Метод класса mainmenu,отвечающий за открытие окна смены пароля.
 */
void mainmenu::on_change_pass_clicked()
{
        change_pass *a=new change_pass(user,this);
        a->setWindowFlag(Qt::Dialog);
        a->setWindowModality(Qt::WindowModal);
        a->show();
}
/*!
 * \brief Метод класса mainmenu,отвечающий за открытие окна получения дополнительного доступа.
 */
void mainmenu::on_Changetar_2_clicked()
{
    Give_admin *a=new Give_admin(user,this);
    a->setWindowFlag(Qt::Dialog);
    a->setWindowModality(Qt::WindowModal);
    a->show();
}
/*!
 * \brief Метод класса mainmenu,отвечающий за обновление окна.
 * \param _login-Имя пользователя.
 * \param _pass-Пароль.
 * \param _adm-Флаг администратора.
 * \param _money-Кол-во денег.
 */
void mainmenu::obnov(const std::string &_login,const std::string &_pass,const bool &_adm,const double &_money)
{
    account user1(_login,_pass,_adm,_money);
    user=user1;
    LastUse h;
    h.put_account(user);
    h.load();
    user.read_all();
    if(user.get_adm()==true)
    {
        QPixmap pix(":/picha/Pichures/MenuScreen.png");
        ui->label_2->setPixmap(pix);
        ui->adinfo->setStyleSheet("QLabel {background-color: rgb(204, 0, 0);color: rgb(255, 255, 255);}");
        ui->adinfo->setText("Вы вошли ,как администратор.");
    }
    else
    {
        QPixmap pix(":/picha/Pichures/MenuScreenUser.png");
        ui->label_2->setPixmap(pix);
        user.home_account();
        ui->Changetar->close();
        ui->Changetar_2->close();
        ui->adinfo->setStyleSheet("QLabel {background-color: rgb(52, 101, 164);color: rgb(255, 255, 255);}");
        ui->adinfo->setText("Вы вошли ,как пользователь.");
    }
    plus_house();
}
/*!
 * \brief Метод класса mainmenu,отвечающий за открытия окна добавления дома.
 */
void mainmenu::on_Newhouse_clicked()
{
    Add_house *a=new Add_house(user,this);
    a->setWindowFlag(Qt::Dialog);
    a->setWindowModality(Qt::WindowModal);
    a->show();
}
/*!
 * \brief Метод класса mainmenu,отвечающий вывод всех домов ,доступных пользователю,на экран.
 */
void mainmenu::plus_house()
{
        ui->Homes->clear();
        std::vector<house>::iterator first=user.get_homes().begin();
        std::vector<house>::iterator last=user.get_homes().end();
        for(;first !=last;first++)
        {
            if(first==user.get_homes().begin())
            {
                QListWidgetItem *a=new QListWidgetItem(QString::fromStdString(first->full_adress()));
                ui->Homes->addItem(a);
                ui->Homes->setCurrentItem(a);
                continue;
            }
            ui->Homes->addItem(QString::fromStdString(first->full_adress()));
        }
}
/*!
 * \brief Метод класса mainmenu,отвечающий за удаление дома.
 */
void mainmenu::on_delete_house_clicked()
{
    if(ui->Homes->selectedItems().size()==0)
    {
        return;
    }
    QMessageBox::StandardButton v=\
    QMessageBox::question(this,"Удаление дома.","Вы уверены ,вся информация о доме \nбудет утеряна?",QMessageBox::Yes | QMessageBox::No);
    if(v==QMessageBox::Yes)
    {
    std::vector<house> a=user.get_homes();
    std::vector<house>::iterator first=a.begin();
    std::vector<house>::iterator last=a.end();
    std::string name=ui->Homes->currentItem()->text().toStdString();
    user.delete_all_house();
    user.read_all();
    for(;first !=last;first++)
    {
        if(first->full_adress()==name)
        {
            user.delete_house(*first);
            break;
        }
    }
    user.save_all();
    user.delete_all_house();
    obnov(user.get_login(),user.get_pass(),user.get_adm(),user.get_money());
    }
}
/*!
 * \brief Метод класса mainmenu,отвечающий за удаление аккаунта.
 */
void mainmenu::on_delacc_clicked()
{
    QMessageBox::StandardButton v=\
    QMessageBox::question(this,"Удаление дома.","Вы уверены ,вся информация об аккаунте \nбудет утеряна?",QMessageBox::Yes | QMessageBox::No);
    if(v==QMessageBox::Yes)
    {
        if(user.delete_acc()==1)
        {
            QMessageBox::information(this,"Предупреждение.","Нельзя удалить единственного\n администратора.");
        }
        else
        {
            on_pushButton_clicked();
            LastUse a;
            a.put_account(user);
            a.dell_acc();
        }
    }
}
/*!
 * \brief Метод класса mainmenu,отвечающий за открытие окна добавления комнаты.
 */
void mainmenu::on_add_room_clicked()
{
    if(ui->Homes->selectedItems().size()==0)
    {
        return;
    }
    std::vector<house> a=user.get_homes();
    std::vector<house>::iterator first=a.begin();
    std::vector<house>::iterator last=a.end();
    std::string name=ui->Homes->currentItem()->text().toStdString();
    user.delete_all_house();
    user.read_all();
    for(;first !=last;first++)
    {
        if(first->full_adress()==name)
        {
            int k=first->get_lives().size()+1;
            add_room *b =new add_room(user,*first,k,k,this);
            b->setWindowFlag(Qt::Dialog);
            user.delete_house(*first);
            user.save_all();
            b->setWindowModality(Qt::WindowModal);
            b->show();
            break;
        }
    }
}
/*!
 * \brief Метод класса mainmenu,отвечающий за открытие окна информации о доме.
 */
void mainmenu::on_info_house_clicked()
{
    if(ui->Homes->selectedItems().size()==0)
    {
        return;
    }
    std::vector<house> a=user.get_homes();
    std::vector<house>::iterator first=a.begin();
    std::vector<house>::iterator last=a.end();
    std::string name=ui->Homes->currentItem()->text().toStdString();
    for(;first !=last;first++)
    {
        if(first->full_adress()==name)
        {
            break;
        }
    }
    info_house_o *b=new info_house_o((*first),this);
    b->setWindowFlag(Qt::Dialog);
    b->setWindowModality(Qt::WindowModal);
    b->show();
}
/*!
 * \brief Метод класса mainmenu,отвечающий за открытие окна удаления комнаты.
 */
void mainmenu::on_dele_room_clicked()
{
    if(ui->Homes->selectedItems().size()==0)
    {
        return;
    }
        std::string _adress=ui->Homes->currentItem()->text().toStdString();
        del_room *a =new del_room(user,_adress,this);
        a->setWindowFlag(Qt::Dialog);
        a->setWindowModality(Qt::WindowModal);
        a->show();
}
/*!
 * \brief Метод класса mainmenu,отвечающий за открытие окна редактирования дома.
 */
void mainmenu::on_Change_h_clicked()
{
    if(ui->Homes->selectedItems().size()==0)
    {
        return;
    }
    std::string str=ui->Homes->currentItem()->text().toStdString();
    Chang_house *a=new Chang_house(user,str,this);
    a->setWindowFlag(Qt::Dialog);
    a->setWindowModality(Qt::WindowModal);
    a->show();
}
/*!
 * \brief Метод класса mainmenu,отвечающий за открытие окна  редактирования комнаты.
 */
void mainmenu::on_chang_room_clicked()
{
    if(ui->Homes->selectedItems().size()==0)
    {
        return;
    }
    std::string str=ui->Homes->currentItem()->text().toStdString();
    Chang_room *a=new Chang_room(user,str,this);
    a->setWindowFlag(Qt::Dialog);
    a->setWindowModality(Qt::WindowModal);
    a->show();

}
/*!
 * \brief Метод класса mainmenu,отвечающий за открытие окна работы с счетчиками.
 */
void mainmenu::on_Countet_butt_clicked()
{
        if(ui->Homes->selectedItems().size()==0)
        {
            return;
        }
        std::string str=ui->Homes->currentItem()->text().toStdString();
        work_counter *a=new work_counter(user,str,this);
        a->setWindowFlag(Qt::Dialog);
        a->setWindowModality(Qt::WindowModal);
        a->show();
}
/*!
 * \brief Метод класса mainmenu,отвечающий за открытие окна работы с приборами.
 */
void mainmenu::on_Devais_butt_clicked()
{
    if(ui->Homes->selectedItems().size()==0)
    {
        return;
    }
    std::string str=ui->Homes->currentItem()->text().toStdString();
    work_dev *a=new work_dev(user,str,this);
    a->setWindowFlag(Qt::Dialog);
    a->setWindowModality(Qt::WindowModal);
    a->show();
}
/*!
 * \brief Метод класса mainmenu,отвечающий за открытие окна работы с датчиками.
 */
void mainmenu::on_Sencor_butt_clicked()
{
    if(ui->Homes->selectedItems().size()==0)
    {
        return;
    }
    std::string str=ui->Homes->currentItem()->text().toStdString();
    work_sen *a=new work_sen(str,user,this);
    a->setWindowFlag(Qt::Dialog);
    a->setWindowModality(Qt::WindowModal);
    a->show();
}
/*!
 * \brief Метод класса mainmenu,отвечающий за открытие окна банковского счета.
 */
void mainmenu::on_bank_clicked()
{
    money *a=new money(user,this);
    a->setWindowFlag(Qt::Dialog);
    a->setWindowModality(Qt::WindowModal);
    a->show();
}
