/*!
  \file
  \brief Файл ,содержащий описание методов класса work_dev.
  */
#include "work_dev.h"
#include "ui_work_dev.h"
#include "mainmenu.h"
#include "add_devais.h"
#include "change_dev.h"
#include "info_dev.h"
/*!
 * \brief Конструктор класса work_dev.
 * \param _user -пользователь.
 * \param adress -адрес дома.
 * \param parent -указатель на родительский класс
 */
work_dev::work_dev(account &_user,std::string &adress,mainmenu *parent) :
    QWidget(parent),
    ui(new Ui::work_dev)
{
    ui->setupUi(this);
    setWindowTitle("\"Умный дом\":Работа с приборами.");
    user=_user;
    user.delete_all_house();
    user.read_all();
    std::vector<house> all=user.get_homes();
    std::vector<house>::iterator first=all.begin();
    for(;;first++)
    {
        if(first->full_adress()==adress)
        {
            dom=*first;
            break;
        }
    }
    listroom();
    on_roomlist_itemSelectionChanged();
}
/*!
 * \brief work_dev::~work_dev
 */
work_dev::~work_dev()
{
    delete ui;
}
/*!
 * \brief Метод класс work_dev,отвечающий за обновление списка комнат.
 */
void work_dev::listroom()
{
    std::vector<room> all= dom.get_lives();
    for(std::vector<room>::iterator first=all.begin();first !=all.end();first++)
    {
        if(first == all.begin())
        {
            QListWidgetItem *a=new QListWidgetItem(QString::fromStdString(first->this_room()));
            ui->roomlist->addItem(a);
            ui->roomlist->setCurrentItem(a);
        }
        else
            ui->roomlist->addItem(QString::fromStdString(first->this_room()));
    }
}
/*!
 * \brief Метод класс work_dev,отвечающий за обновление списка девайсов.
 */
void work_dev::on_roomlist_itemSelectionChanged()
{
    ui->devlist->clear();
    std::vector<room> all= dom.get_lives();
    std::vector<room>::iterator first=all.begin();
    for(;;first++)
    {
        if(first->this_room()==ui->roomlist->currentItem()->text().toStdString())
        {
            komn=*(first);
            break;
    }
    }
    std::vector<devais> all_dev=first->get_dev();
    for(std::vector<devais>::iterator first1=all_dev.begin();first1 !=all_dev.end();first1++)
    {
        if(first1 == all_dev.begin())
        {
                 QListWidgetItem *a=new QListWidgetItem(QString::fromStdString(first1->get_name()));
                 ui->devlist->addItem(a);
                 ui->devlist->setCurrentItem(a);
        }
        else
                 ui->devlist->addItem(QString::fromStdString(first1->get_name()));
    }
    ui->warning->setStyleSheet("(QLabel {background-color: rgba(204, 0, 0,1)");
    ui->warning->clear();

}
/*!
 * \brief Метод класс work_dev,отвечающий за вывод информации об успешном добавление прибора.
 */
void work_dev::ok_new_dev()
{
    ui->warning->setStyleSheet("QLabel {background-color:rgb(32, 180, 28);color: rgb(238, 238, 236);}");
    ui->warning->setText("Прибор успешно добавлен.");
}
/*!
 * \brief Метод класс work_dev,отвечающий за открытие окна добавления девайсов.
 */
void work_dev::on_add_dev_clicked()
{
    if((!komn.get_sensor(1).get_norm() && komn.get_sensor(1).get_have() &&komn.get_sensor(1).get_on()) ||\
                (!komn.get_sensor(2).get_norm() && komn.get_sensor(2).get_have() &&komn.get_sensor(2).get_on()))
        {
                ui->warning->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
                ui->warning->setText("Нельзя установить прибор при сработавших датчиках.");
                return;
        }
    if(user.get_money()<=0)
    {
        ui->warning->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
        ui->warning->setText("У вас не достаточно средств.");
        return;
    }
    add_devais *a=new add_devais(user,dom,komn,this);
    a->setWindowFlag(Qt::Dialog);
    a->setWindowModality(Qt::WindowModal);
    a->show();
}
/*!
 * \brief Метод класс work_dev,отвечающий за включение прибора.
 */
void work_dev::on_on_true_clicked()
{
    if(user.get_money()<=0)
    {
        ui->warning->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
        ui->warning->setText("У вас не хватает денег.");
        return;
    }
    if((!komn.get_sensor(1).get_norm() && komn.get_sensor(1).get_have() &&komn.get_sensor(1).get_on()) ||\
                (!komn.get_sensor(2).get_norm() && komn.get_sensor(2).get_have() &&komn.get_sensor(2).get_on()))
        {
                ui->warning->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
                ui->warning->setText("Нельзя включить прибор при сработавших датчиках.");
                return;
        }
    if(ui->devlist->selectedItems().size()==0)
    {
        return;
    }
    std::vector<devais> all= komn.get_dev();
    std::vector<devais>::iterator first=all.begin();
    for(;;first++)
    {
        if(first->get_name()== ui->devlist->currentItem()->text().toStdString())
        {
            if(first->get_on()==true)
            {
                ui->warning->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
                ui->warning->setText("Прибор уже включен.");
                return;
            }
            else
            {
                break;
            }
        }
    }
    devais one;
    one=*first;
    one.on_off(true);
    user.delete_all_house();
    user.delete_devais(dom,komn,one);
    user.delete_all_house();
    user.push_devais(one,dom,komn);
    obnov();
    ui->warning->setStyleSheet("QLabel {background-color:rgb(32, 180, 28);color: rgb(238, 238, 236);}");
    ui->warning->setText("Прибор успешно включен.");
}
/*!
 * \brief Метод класс work_dev,отвечающий за отключение прибора.
 */
void work_dev::on_on_false_clicked()
{
    if(ui->devlist->selectedItems().size()==0)
    {
        return;
    }
    std::vector<devais> all= komn.get_dev();
    std::vector<devais>::iterator first=all.begin();
    for(;;first++)
    {
        if(first->get_name()== ui->devlist->currentItem()->text().toStdString())
        {
            if(first->get_on()==false)
            {
                ui->warning->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
                ui->warning->setText("Прибор уже выключен.");
                return;
            }
            else
            {
                break;
            }
        }
    }
    devais one;
    one=*first;
    one.on_off(false);
    user.delete_all_house();
    user.delete_devais(dom,komn,one);
    user.delete_all_house();
    user.push_devais(one,dom,komn);
    obnov();
    ui->warning->setStyleSheet("QLabel {background-color:rgb(32, 180, 28);color: rgb(238, 238, 236);}");
    ui->warning->setText("Прибор успешно выключен.");  
}
/*!
 * \brief Метод класс work_dev,отвечающий за открытие окна редактирования девайса.
 */
void work_dev::on_change_dev_clicked()
{
    if(ui->devlist->selectedItems().size()==0)
    {
        return;
    }
    std::vector<devais> all= komn.get_dev();
    std::vector<devais>::iterator first=all.begin();
    for(;;first++)
    {
        if(first->get_name()== ui->devlist->currentItem()->text().toStdString())
        {
            break;
        }
    }
    change_dev *a=new change_dev(dom,komn,*first,this);
    a->setWindowFlag(Qt::Dialog);
    a->setWindowModality(Qt::WindowModal);
    a->show();
}
/*!
 * \brief Метод класс work_dev,отвечающий за открытие окна с информацией о девайсе.
 */
void work_dev::on_info_dev_clicked()
{
    if(ui->devlist->selectedItems().size()==0)
    {
        return;
    }
    std::vector<devais> all= komn.get_dev();
    std::vector<devais>::iterator first=all.begin();
    for(;;first++)
    {
        if(first->get_name()== ui->devlist->currentItem()->text().toStdString())
        {
            break;
        }
    }
    info_dev *a=new info_dev(dom,komn,*first,this);
    a->setWindowFlag(Qt::Dialog);
    a->setWindowModality(Qt::WindowModal);
    a->show();
}
/*!
 * \brief Метод класс work_dev,отвечающий за демонтаж девайса.
 */
void work_dev::on_delete_pr_clicked()
{
    if(ui->devlist->selectedItems().size()==0)
    {
        return;
    }
    std::vector<devais> all= komn.get_dev();
    std::vector<devais>::iterator first=all.begin();
    for(;;first++)
    {
        if(first->get_name()== ui->devlist->currentItem()->text().toStdString())
        {
            break;
        }
    }
    user.delete_all_house();
    user.delete_devais(dom,komn,*first);
    obnov();
    ui->warning->setStyleSheet("QLabel {background-color:rgb(32, 180, 28);color: rgb(238, 238, 236);}");
    ui->warning->setText("Прибор успешно удален.");

}
/*!
 * \brief Метод класс work_dev,отвечающий за выход из окна.
 */
void work_dev::on_back_clicked()
{
    delete this;
}
/*!
 * \brief Метод класс work_dev,отвечающий за обновление окна.
 */
void work_dev::obnov()
{
    user.delete_all_house();
    user.read_all();
    std::vector<house> all=user.get_homes();
    std::vector<house>::iterator first=all.begin();
    for(;;first++)
    {
        if(first->full_adress()==dom.full_adress())
        {
            dom=*first;
            break;
        }
    }
    on_roomlist_itemSelectionChanged();
}
