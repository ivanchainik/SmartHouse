/*!
  \file
  \brief Файл,содержащий описание методов класса work_sen.
  */
#include "work_sen.h"
#include "ui_work_sen.h"
#include "add_cond.h"
#include "cond.h"
/*!
 * \brief Конструктор класса work_sen.
 * \param _adress -адрес дома.
 * \param _user -пользователь.
 * \param parent -указатель на родительский класс.
 */
work_sen::work_sen(const std::string _adress,const account &_user,mainmenu *parent) :
    QWidget(parent),
    ui(new Ui::work_sen)
{
    ui->setupUi(this);
    user=_user;
    par=parent;
    adress=_adress;
    obnov();
    setWindowTitle("\"Умный дом\":Работа с датчиками.");
}
/*!
 * \brief Деструктор класса work_sen.
 */
work_sen::~work_sen()
{
    delete ui;
}
/*!
 * \brief Метод класса work_sen, отвечающий за выход из окна.
 */
void work_sen::on_back_clicked()
{
    delete this;
}
/*!
 * \brief Метод класса work_sen, отвечающий за обновления списка комнат.
 */
void work_sen::roomlist()
{
    std::vector<room> all=dom.get_lives();
    std::vector<room>::iterator first=all.begin();
    for(;first!=all.end();first++)
    {
        if(first==all.begin())
        {
            QListWidgetItem *a=new  QListWidgetItem(QString::fromStdString(first->this_room()));
            ui->roomlist->addItem(a);
            ui->roomlist->setCurrentItem(a);
        }
        else
        {
            ui->roomlist->addItem(QString::fromStdString(first->this_room()));
        }
    }
}
/*!
 * \brief Метод класса work_sen, отвечающий за обновление информации о датчиках.
 */
void work_sen::on_roomlist_itemSelectionChanged()
{
    ui->warning->setStyleSheet("QLabel {background-color: rgba(204, 0, 0,1)");
    ui->warning->clear();
    std::vector<room> all=dom.get_lives();
    std::vector<room>::iterator first=all.begin();
    for(;;first++)
    {
        if(first->this_room()==ui->roomlist->currentItem()->text().toStdString())
        {
            break;
        }
    }
    komn=*first;
    if(komn.get_sensor(1).get_have()==true)
    {
        ui->water_have->setStyleSheet("QLabel {background-color:rgb(32, 180, 28);color: rgb(238, 238, 236);}");
        ui->water_have->setText("Установлен.");
        if(komn.get_sensor(1).get_on()==true)
        {
            ui->water_on->setStyleSheet("QLabel {background-color:rgb(32, 180, 28);color: rgb(238, 238, 236);}");
            ui->water_on->setText("Включен.");
            double a=komn.get_sensor(1).get_proc();
            ui->water_proc->setText(QString("%1").arg(a)+"%");
            if(a<=15)
            {
                ui->water_norm->setStyleSheet("QLabel {background-color:rgb(32, 180, 28);color: rgb(238, 238, 236);}");
                ui->water_norm->setText("В пределах нормы.");
            }
            else if(a<=45)
            {
                ui->water_norm->setStyleSheet("QLabel {background-color:rgb(237, 212, 0);color: rgb(238, 238, 236);}");
                ui->water_norm->setText("Выше нормы.");
            }
            else
            {
                ui->water_norm->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
                ui->water_norm->setText("Сильно выше нормы.");
            }
        }
        else
        {
            clear_water();
            ui->water_on->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
            ui->water_on->setText("Выключен.");
        }
    }
    else
    {
        clear_water();
        ui->water_have->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
        ui->water_have->setText("Не установлен.");
        ui->water_on->setStyleSheet("QLabel {background-color: rgba(204, 0, 0,1)");
        ui->water_on->clear();
    }

    if(komn.get_sensor(2).get_have()==true)
    {
        ui->gas_have->setStyleSheet("QLabel {background-color:rgb(32, 180, 28);color: rgb(238, 238, 236);}");
        ui->gas_have->setText("Установлен.");
        if(komn.get_sensor(2).get_on()==true)
        {
            ui->gas_on->setStyleSheet("QLabel {background-color:rgb(32, 180, 28);color: rgb(238, 238, 236);}");
            ui->gas_on->setText("Включен.");
            double a=komn.get_sensor(2).get_proc();
            ui->gas_proc->setText(QString("%1").arg(a)+"%");
            if(a<=15)
            {
                ui->gas_norm->setStyleSheet("QLabel {background-color:rgb(32, 180, 28);color: rgb(238, 238, 236);}");
                ui->gas_norm->setText("В пределах нормы.");
            }
            else if(a<=45)
            {
                ui->gas_norm->setStyleSheet("QLabel {background-color:rgb(237, 212, 0);color: rgb(238, 238, 236);}");
                ui->gas_norm->setText("Выше нормы.");
            }
            else
            {
                ui->gas_norm->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
                ui->gas_norm->setText("Сильно выше нормы.");
            }
        }
        else
        {
            clear_gas();
            ui->gas_on->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
            ui->gas_on->setText("Выключен.");
        }
    }
    else
    {
        ui->gas_have->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
        ui->gas_have->setText("Не установлен.");
        ui->gas_on->setStyleSheet("QLabel {background-color: rgba(204, 0, 0,1)");
        ui->gas_on->clear();
        clear_gas();
    }
    if(komn.get_temp_sen().get_have()==true)
    {
        ui->temp_have->setStyleSheet("QLabel {background-color:rgb(32, 180, 28);color: rgb(238, 238, 236);}");
        ui->temp_have->setText("Установлен.");
        if(komn.get_temp_sen().get_on()==true)
        {
            ui->temp_on->setStyleSheet("QLabel {background-color:rgb(32, 180, 28);color: rgb(238, 238, 236);}");
            ui->temp_on->setText("Включен.");
            double a=komn.get_temp_sen().get_temp();
            ui->temp_proc->setText(QString("%1").arg(a)+"C");
            if(a<15)
            {
                ui->temp_norm->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
                ui->temp_norm->setText("Ниже нормы.");
            }
            else if(a>=15 && a<=25)
            {
                ui->temp_norm->setStyleSheet("QLabel {background-color:rgb(32, 180, 28);color: rgb(238, 238, 236);}");
                ui->temp_norm->setText("Норма.");
            }
            else
            {
                ui->temp_norm->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
                ui->temp_norm->setText("Сильно выше нормы.");
            }
            ui->cond_have_true->show();
            QPixmap b (":/picha/Pichures/work_sen3.png");
            ui->label_5->setPixmap(b);
            if(komn.get_temp_sen().get_cond_have()==false)
            {
                ui->cond_on->setStyleSheet("QLabel {background-color: rgba(204, 0, 0,1)");
                ui->cond_on->clear();
                ui->energy->clear();
                ui->cond_have_false->close();
                ui->cond_on_but->close();
            }
            else
            {
                QPixmap a (":/picha/Pichures/work_sen.png");
                ui->label_5->setPixmap(a);
                if(komn.get_temp_sen().get_cond_on()==true)
                {
                    ui->cond_on->setStyleSheet("QLabel {background-color:rgb(32, 180, 28);color: rgb(238, 238, 236);}");
                    ui->cond_on->setText("Кондиционер включен.");
                }
                else
                {
                    ui->cond_on->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
                    ui->cond_on->setText("Кондиционер вылючен.");
                }
                ui->energy->setText(QString("%1").arg(komn.get_temp_sen().get_electr()));
                ui->cond_have_false->show();
                ui->cond_on_but->show();
            }
        }
        else
        {
            clear_temp();
            ui->temp_on->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
            ui->temp_on->setText("Выключен.");
        }
    }
    else
    {
        ui->temp_have->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
        ui->temp_have->setText("Не установлен.");
        ui->temp_on->setStyleSheet("QLabel {background-color: rgba(204, 0, 0,1)");
        ui->temp_on->clear();
        clear_temp();
    }
}
/*!
 * \brief Метод класса work_sen, отвечающий за удаление информации о датчике наводнения.
 */
void work_sen::clear_water()
{
    ui->water_norm->setStyleSheet("QLabel {background-color: rgba(204, 0, 0,1)");
    ui->water_norm->clear();
    ui->water_proc->clear();
}
/*!
 * \brief Метод класса work_sen, отвечающий за удаление информации о датчике задымления.
 */
void work_sen::clear_gas()
{
    ui->gas_norm->setStyleSheet("QLabel {background-color: rgba(204, 0, 0,1)");
    ui->gas_norm->clear();
    ui->gas_proc->clear();
}
/*!
 * \brief Метод класса work_sen, отвечающий за удаление информации о датчике температуры.
 */
void work_sen::clear_temp()
{
    ui->temp_norm->setStyleSheet("QLabel {background-color: rgba(204, 0, 0,1)");
    ui->temp_norm->clear();
    ui->temp_proc->clear();
    ui->cond_on->setStyleSheet("QLabel {background-color: rgba(204, 0, 0,1)");
    ui->cond_on->clear();
    ui->energy->clear();
    ui->cond_have_true->close();
    ui->cond_have_false->close();
    ui->cond_on_but->close();
    QPixmap a (":/picha/Pichures/work_sen2.png");
    ui->label_5->setPixmap(a);
}
/*!
 * \brief Метод класса work_sen, отвечающий за установку датчиков.
 */
void work_sen::on_have_true_clicked()
{
    if((ui->water_set->isChecked()==true && komn.get_sensor(1).get_have()==true) || \
            (ui->gas_set->isChecked()==true && komn.get_sensor(2).get_have()==true) || \
             (ui->temp_set->isChecked()==true && komn.get_temp_sen().get_have()==true) )
     {
         ui->warning->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
         ui->warning->setText("\t\t\t Нельзя установить установленный датчик.");
         return;
     }

    bool on=true;
    double proc=0;
    sencor a;
    a.put_sencor(on,on,proc);
    a.on_off(on);
    if(ui->water_set->isChecked())
    {
        komn.get_sensor(1)=a;
    }
    if(ui->gas_set->isChecked())
    {
        komn.get_sensor(2)=a;
    }
    if(ui->temp_set->isChecked())
    {
        bool off=false;
        double temp=abs(rand()%20)+10;
        temperature b;
        b.put_sencor(on,on,proc);
        b.put_temp(off,temp,off);
        b.on_off(on);
        komn.get_temp_sen()=b;
    }
    dom.delete_room(komn);
    dom.in_vector(komn);
    user.delete_house(dom);
    user.in_vector(dom);
    user.save_all();
    ui->warning->setStyleSheet("QLabel {background-color:rgb(32, 180, 28);color: rgb(238, 238, 236);}");
    obnov();
    ui->warning->setText("\t\t\t Датчики успешно подключены.");
}
/*!
 * \brief Метод класса work_sen, отвечающий за обновление окна.
 */
void work_sen::obnov()
{
    ui->roomlist->clear();
    user.delete_all_house();
    user.read_all();
    if(user.get_adm()==false)
    {
        ui->simulat->close();
    }
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
    roomlist();
    par->obnov(user.get_login(),user.get_login(),user.get_adm(),user.get_money());
}
/*!
 * \brief Метод класса work_sen, отвечающий за демонтаж датчиков.
 */
void work_sen::on_have_false_clicked()
{
    if((ui->water_set->isChecked()==true && !komn.get_sensor(1).get_have()) || \
           (ui->gas_set->isChecked()==true && !komn.get_sensor(2).get_have()) || \
            (ui->temp_set->isChecked()==true && !komn.get_temp_sen().get_have()) )
    {
        ui->warning->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
        ui->warning->setText("\t\t\t Нельзя демонтировать не установленный датчик.");
        return;
    }

    bool on=false;
    double proc=0;
    sencor a;
    a.put_sencor(on,on,proc);
    a.on_off(on);
    if(ui->water_set->isChecked())
    {
        komn.get_sensor(1)=a;
    }
    if(ui->gas_set->isChecked())
    {
        komn.get_sensor(2)=a;
    }
    if(ui->temp_set->isChecked())
    {
        bool off=false;
        double temp=abs(rand()%20)+10;
        temperature b;
        b.put_sencor(on,on,proc);
        b.put_temp(off,temp,off);
        b.on_off(on);
        komn.get_temp_sen()=b;
    }
    dom.delete_room(komn);
    dom.in_vector(komn);
    user.delete_house(dom);
    user.in_vector(dom);
    user.save_all();
    ui->warning->setStyleSheet("QLabel {background-color:rgb(32, 180, 28);color: rgb(238, 238, 236);}");
    obnov();
    ui->warning->setText("\t\t\t Датчики успешно демонтированы.");

}
/*!
 * \brief Метод класса work_sen, отвечающий за включение датчиков.
 */
void work_sen::on_on_true_clicked()
{
    if((ui->water_set->isChecked()==true && !komn.get_sensor(1).get_have()) || \
           (ui->gas_set->isChecked()==true && !komn.get_sensor(2).get_have()) || \
            (ui->temp_set->isChecked()==true && !komn.get_temp_sen().get_have()) )
    {
        ui->warning->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
        ui->warning->setText("\t\t\t Нельзя включить не установленный датчик.");
        return;
    }
    if((ui->water_set->isChecked() && komn.get_sensor(1).get_on()) || \
        (ui->gas_set->isChecked() && komn.get_sensor(2).get_on())|| \
        (ui->temp_set->isChecked() && komn.get_temp_sen().get_on()))
    {
        ui->warning->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
        ui->warning->setText("\t\t\t Нельзя включить включенный датчик.");
        return;
    }
    bool on=true;
    if(ui->water_set->isChecked())
    {
        komn.get_sensor(1).on_off(on);
    }
    if(ui->gas_set->isChecked())
    {
        komn.get_sensor(2).on_off(on);
    }
    if(ui->temp_set->isChecked())
    {
        komn.get_temp_sen().on_off(on);
    }
    dom.delete_room(komn);
    dom.in_vector(komn);
    user.delete_house(dom);
    user.in_vector(dom);
    user.save_all();
    ui->warning->setStyleSheet("QLabel {background-color:rgb(32, 180, 28);color: rgb(238, 238, 236);}");
    obnov();
    ui->warning->setText("\t\t\t Датчики успешно включены.");
}
/*!
 * \brief Метод класса work_sen, отвечающий за выключение датчиков.
 */
void work_sen::on_on_false_clicked()
{
    if((ui->water_set->isChecked()==true && !komn.get_sensor(1).get_have()) || \
           (ui->gas_set->isChecked()==true && !komn.get_sensor(2).get_have()) || \
            (ui->temp_set->isChecked()==true && !komn.get_temp_sen().get_have()) )
    {
        ui->warning->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
        ui->warning->setText("\t\t\t Нельзя выключить не установленный датчик.");
        return;
    }
    if((ui->water_set->isChecked() && !komn.get_sensor(1).get_on()) || \
        (ui->gas_set->isChecked() && !komn.get_sensor(2).get_on())|| \
        (ui->temp_set->isChecked() && !komn.get_temp_sen().get_on()))
    {
        ui->warning->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
        ui->warning->setText("\t\t\t Нельзя выключить выключенный датчик.");
        return;
    }
    bool on=false;
    if(ui->water_set->isChecked())
    {
        komn.get_sensor(1).on_off(on);
    }
    if(ui->gas_set->isChecked())
    {
        komn.get_sensor(2).on_off(on);
    }
    if(ui->temp_set->isChecked())
    {
        komn.get_temp_sen().on_off(on);
    }
    dom.delete_room(komn);
    dom.in_vector(komn);
    user.delete_house(dom);
    user.in_vector(dom);
    user.save_all();
    ui->warning->setStyleSheet("QLabel {background-color:rgb(32, 180, 28);color: rgb(238, 238, 236);}");
    obnov();
    ui->warning->setText("\t\t\t Датчики успешно включены.");

}
/*!
 * \brief Метод класса work_sen, отвечающий за симуляцию реальной ситуации.
 */
void work_sen::on_simulat_clicked()
{
    double a=abs(rand()%100);
    bool _have;
    bool _norm;

    if(komn.get_sensor(1).get_have())
    {_have=komn.get_sensor(1).get_have();
    if(45 < a)
    {
        _norm=false;
    }
    else
    {
        _norm=true;
    }
    komn.get_sensor(1).put_sencor(_have,_norm,a);
    }
    if(komn.get_sensor(2).get_have())
    {
    a=abs(rand()%100);
    _have=komn.get_sensor(2).get_have();
    if(45 < a)
    {
        _norm=false;
    }
    else
    {
        _norm=true;
    }
    komn.get_sensor(2).put_sencor(_have,_norm,a);
    }
    if(komn.get_temp_sen().get_cond_on());
    else
    {
        a=abs(rand()%30);
        _have=komn.get_temp_sen().get_cond_have();
        _norm=komn.get_temp_sen().get_cond_on();
        komn.get_temp_sen().put_temp(_norm,a,_have);
    }
    dom.delete_room(komn);
    dom.in_vector(komn);
    user.delete_house(dom);
    user.in_vector(dom);
    if((!komn.get_sensor(1).get_norm() && komn.get_sensor(1).get_have() &&komn.get_sensor(1).get_on()) ||\
            (!komn.get_sensor(2).get_norm() && komn.get_sensor(2).get_have() &&komn.get_sensor(2).get_on()))
    {
        user.off_devais(dom,1);
        user.off_devais(dom,2);
        user.off_devais(dom,2);
    }
    user.save_all();
    ui->warning->setStyleSheet("QLabel {background-color:rgb(32, 180, 28);color: rgb(238, 238, 236);}");
    obnov();
    ui->warning->setText("\t\t\t Датчики успешно симулированны.");


}
/*!
 * \brief Метод класса work_sen, отвечающий за установку кондиционера.
 */
void work_sen::on_cond_have_true_clicked()
{
    if(komn.get_temp_sen().get_cond_have()==true )
    {
        ui->warning->setStyleSheet("QLabel {background-color:rgb(204,0,0);color: rgb(238, 238, 236);}");
        ui->warning->setText("\t\t\t\t\t Кондиционер уже установлен.");
    }
    else if(user.get_money()<=0)
    {
        ui->warning->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
        ui->warning->setText("У вас не достаточно средств.");
    }
    else
    {
        add_cond *a=new add_cond(dom,komn,this);
        a->setWindowFlag(Qt::Dialog);
        a->setWindowModality(Qt::WindowModal);
        a->show();
    }
}
/*!
 * \brief Метод класса work_sen, отвечающий за демонтаж кондиционера.
 */
void work_sen::on_cond_have_false_clicked()
{
    double temp=komn.get_temp_sen().get_temp();
    bool a=false;
    komn.get_temp_sen().put_temp(a,temp,a);
    dom.delete_room(komn);
    dom.in_vector(komn);
    user.delete_house(dom);
    user.in_vector(dom);
    user.save_all();
    obnov();
    ui->warning->setStyleSheet("QLabel {background-color:rgb(32, 180, 28);color: rgb(238, 238, 236);}");
    ui->warning->setText("\t\t\t Изменения успешны.");

}
/*!
 * \brief Метод класса work_sen, отвечающий за включение/отключение кондиционера.
 */
void work_sen::on_cond_on_but_clicked()
{
    if(komn.get_temp_sen().get_cond_on())
    {
        bool a=false;
        bool b=true;
        double c=komn.get_temp_sen().get_temp();
        komn.get_temp_sen().put_temp(a,c,b);
        dom.delete_room(komn);
        dom.in_vector(komn);
        user.delete_house(dom);
        user.in_vector(dom);
        user.save_all();
        obnov();
        ui->warning->setStyleSheet("QLabel {background-color:rgb(32, 180, 28);color: rgb(238, 238, 236);}");
        ui->warning->setText("\t\t\t Изменения успешны.");
    }
    else if((!komn.get_sensor(1).get_norm() && komn.get_sensor(1).get_have() &&komn.get_sensor(1).get_on()) ||\
            (!komn.get_sensor(2).get_norm() && komn.get_sensor(2).get_have() &&komn.get_sensor(2).get_on()))
    {
            ui->warning->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
            ui->warning->setText("Нельзя включить прибор при сработавших датчиках.");
    }
    else if(user.get_money()<=0)
    {
        ui->warning->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
        ui->warning->setText("У вас не достаточно средств.");
   }
    else
    {
        cond *a=new cond(dom,komn,this);
        a->setWindowFlag(Qt::Dialog);
        a->setWindowModality(Qt::WindowModal);
        a->show();
        ui->warning->setStyleSheet("QLabel {background-color:rgb(32, 180, 28);color: rgb(238, 238, 236);}");
        ui->warning->setText("\t\t\t Изменения успешны.");
    }
}
