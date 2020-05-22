/*!
  \file
  \brief Файл ,содержащий описание методов класса work_counter.
 */
#include "work_counter.h"
#include "ui_work_counter.h"
#include <vector>
#include "mainmenu.h"
#include "tarif.h"
/*!
 * \brief Конструктор класса work_counter.
 * \param a -аккаунт пользователя.
 * \param _adress -адрес дома.
 * \param parent -указатель на родительский класс.
 */
work_counter::work_counter(account &a,std::string &_adress,mainmenu *parent):
    QWidget(parent),
    ui(new Ui::work_counter)
{
    par=parent;
    user=a;
    adress=_adress;
    ui->setupUi(this);
    obnov();
    setWindowTitle("\"Умный дом\":Работа с cчетчиками.");
}
/*!
 * \brief Деструктор класса work_counter.
 */
work_counter::~work_counter()
{
    delete ui;
}
/*!
 * \brief Метод класса work_counter, отвечающий за выход из окна.
 */
void work_counter::on_pushButton_clicked()
{
    delete this;
}
/*!
 * \brief Метод класса work_counter, отвечающий за обновление окна.
 */
void work_counter::obnov()
{
    if(!user.get_adm())
    ui->norm_false->close();
    tarif tar;
    user.delete_all_house();
    user.read_all();
    std::vector<house> all=user.get_homes();
    std::vector<house>::iterator first=all.begin();
    std::vector<house>::iterator last=all.end();
    for(;first!=last;first++)
    {
        if(first->full_adress()== adress)
        {
            home=*first;
            break;
        }
    }
    if(home.get_sencor(1).get_have()==true)
    {
        ui->have_electr->setStyleSheet("QLabel {background-color:rgb(32, 180, 28);color: rgb(238, 238, 236);}");
        ui->have_electr->setText("Установлен.");
        if(home.get_sencor(1).get_on()==true)
        {
            ui->on_electr->setStyleSheet("QLabel {background-color:rgb(32, 180, 28);color: rgb(238, 238, 236);}");
            ui->on_electr->setText("Включен.");
            if(home.get_sencor(1).get_norm()==true)
            {
                ui->norm_elect->setStyleSheet("QLabel {background-color:rgb(32, 180, 28);color: rgb(238, 238, 236);}");
                ui->norm_elect->setText("Нормально функционирует.");
                ui->val_elect->setText(QString("%1").arg(home.get_sencor(1).get_value()));
                ui->val_electr_tar->setText(QString("%1").arg(home.get_sencor(1).get_value()*tar.get_electr()));
                ui->speed_electr->setText(QString("%1").arg(home.sum_electr()));
                ui->speed_electr_tar->setText(QString("%1").arg(home.sum_electr()*tar.get_electr()));
                ui->last_elecrt->setText(QString("%3").arg(home.get_last_val(1,1)));
                ui->electr_last_tar->setText(QString("%3").arg(home.get_last_val(1,2)));
            }
            else
            {
                ui->norm_elect->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
                ui->norm_elect->setText("\t Сломан.");
                clear_electr();
            }

        }
        else
        {
            ui->norm_elect->setStyleSheet("QLabel {background-color: rgba(204, 0, 0,1)");
            ui->norm_elect->clear();
            ui->on_electr->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
            ui->on_electr->setText("Выключен.");
            clear_electr();
        }
    }
    else
    {
        ui->have_electr->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
        ui->have_electr->setText("Не установлен.");
        ui->norm_elect->setStyleSheet("QLabel {background-color: rgba(204, 0, 0,1)");
        ui->on_electr->setStyleSheet("(QLabel {background-color: rgba(204, 0, 0,1)");
        ui->on_electr->clear();
        ui->norm_elect->clear();
        clear_electr();
    }

    if(home.get_sencor(2).get_have()==true)
    {
        ui->have_gas->setStyleSheet("QLabel {background-color:rgb(32, 180, 28);color: rgb(238, 238, 236);}");
        ui->have_gas->setText("Установлен.");
        if(home.get_sencor(2).get_on()==true)
        {
            ui->on_gas->setStyleSheet("QLabel {background-color:rgb(32, 180, 28);color: rgb(238, 238, 236);}");
            ui->on_gas->setText("Включен.");
            if(home.get_sencor(2).get_norm()==true)
            {
                ui->norm_gas->setStyleSheet("QLabel {background-color:rgb(32, 180, 28);color: rgb(238, 238, 236);}");
                ui->norm_gas->setText("Нормально функционирует.");
                ui->val_gas->setText(QString("%1").arg(home.get_sencor(2).get_value()));
                ui->val_gas_tar->setText(QString("%1").arg(home.get_sencor(2).get_value()*tar.get_gaz()));
                ui->speed_gas->setText(QString("%1").arg(home.sum_gas()));
                ui->speed_gas_tar->setText(QString("%1").arg(home.sum_gas()*tar.get_gaz()));
                ui->last_gas->setText(QString("%3").arg(home.get_last_val(3,1)));
                ui->gas_last_tar->setText(QString("%3").arg(home.get_last_val(3,2)));
            }
            else
            {
                ui->norm_gas->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
                ui->norm_gas->setText("\t Сломан.");
                clear_gas();
            }

        }
        else
        {
            ui->norm_gas->clear();
            ui->norm_gas->setStyleSheet("QLabel {background-color: rgba(204, 0, 0,1)");
            ui->on_gas->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
            ui->on_gas->setText("Выключен.");
            clear_gas();
        }
    }
    else
    {
        ui->have_gas->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
        ui->have_gas->setText("Не установлен.");
        ui->norm_gas->setStyleSheet("QLabel {background-color: rgba(204, 0, 0,1)");
        ui->on_gas->setStyleSheet("(QLabel {background-color: rgba(204, 0, 0,1)");
        ui->on_gas->clear();
        ui->norm_gas->clear();
        clear_gas();
    }

    if(home.get_sencor(3).get_have()==true)
    {
        ui->have_water->setStyleSheet("QLabel {background-color:rgb(32, 180, 28);color: rgb(238, 238, 236);}");
        ui->have_water->setText("Установлен.");
        if(home.get_sencor(3).get_on()==true)
        {
            ui->on_water->setStyleSheet("QLabel {background-color:rgb(32, 180, 28);color: rgb(238, 238, 236);}");
            ui->on_water->setText("Включен.");
            if(home.get_sencor(3).get_norm()==true)
            {
                ui->norm_water->setStyleSheet("QLabel {background-color:rgb(32, 180, 28);color: rgb(238, 238, 236);}");
                ui->norm_water->setText("Нормально функционирует.");
                ui->val_water->setText(QString("%1").arg(home.get_sencor(3).get_value()));
                ui->val_water_tar->setText(QString("%1").arg(home.get_sencor(3).get_value()*tar.get_water()));
                ui->speed_water->setText(QString("%1").arg(home.sum_water()));
                ui->speed_water_tar->setText(QString("%1").arg(home.sum_water()*tar.get_water()));
                ui->last_water->setText(QString("%3").arg(home.get_last_val(2,1)));
                ui->water_last_tar->setText(QString("%3").arg(home.get_last_val(2,2)));
            }
            else
            {
                ui->norm_water->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
                ui->norm_water->setText("\t Сломан.");
                clear_water();
            }

        }
        else
        {
            ui->norm_water->clear();
            ui->norm_water->setStyleSheet("QLabel {background-color: rgba(204, 0, 0,1)");
            ui->on_water->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
            ui->on_water->setText("Выключен.");
            clear_water();
        }
    }
    else
    {
        ui->have_water->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
        ui->have_water->setText("Не установлен.");
        ui->norm_water->setStyleSheet("QLabel {background-color: rgba(204, 0, 0,1)");
        ui->on_water->setStyleSheet("(QLabel {background-color: rgba(204, 0, 0,1)");
        ui->on_water->clear();
        ui->norm_water->clear();
        clear_water();
    }
}
/*!
 * \brief Метод класса work_counter, отвечающий за очищение информации о электричестве на окне.
 */
void work_counter::clear_electr()
{
    ui->electr_last_tar->clear();
    ui->last_elecrt->clear();
    ui->val_electr_tar->clear();
    ui->val_elect->clear();
    ui->speed_electr->clear();
    ui->speed_electr_tar->clear();
}
/*!
 * \brief Метод класса work_counter, отвечающий за очищение информации о газе на окне.
 */
void work_counter::clear_gas()
{
    ui->gas_last_tar->clear();
    ui->last_gas->clear();
    ui->val_gas_tar->clear();
    ui->val_gas->clear();
    ui->speed_gas->clear();
    ui->speed_gas_tar->clear();
}
/*!
 * \brief Метод класса work_counter, отвечающий за очищение информации о воде на окне.
 */
void work_counter::clear_water()
{
    ui->water_last_tar->clear();
    ui->val_water_tar->clear();
    ui->last_water->clear();
    ui->val_water->clear();
    ui->speed_water->clear();
    ui->speed_water_tar->clear();
}
/*!
 * \brief Метод класса work_counter, отвечающий за включение счетчика.
 */
void work_counter::on_on_true_clicked()
{
    bool _on=true;
    if (!(ui->c_elecrt->isChecked() || ui->c_gas->isChecked() || ui->c_water->isChecked()))
    {
        ui->warning->setStyleSheet("QLabel {background-color: rgba(204, 0, 0,1)");
        ui->warning->clear();
        return;
    }
    if((ui->c_elecrt->isChecked() && !(home.get_sencor(1).get_have())) || (ui->c_gas->isChecked() && !(home.get_sencor(2).get_have())) \
      ||   (ui->c_water->isChecked() && !(home.get_sencor(3).get_have())))
    {
        ui->warning->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
        ui->warning->setText("\t\t\t\t\t\tНельзя включить не установленный счетчик.");
        return;
    }
    if((ui->c_elecrt->isChecked() && home.get_sencor(1).get_on()) || (ui->c_gas->isChecked() && home.get_sencor(2).get_on()) \
            || (ui->c_water->isChecked() && home.get_sencor(3).get_on()))
    {
        ui->warning->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
        ui->warning->setText("\t\t\t\t\t\tНельзя включить включенный счетчик.");
    }
    else
    {
        if(ui->c_elecrt->isChecked())
        {
            home.get_sencor(1).on_off(_on);
        }
        if(ui->c_gas->isChecked())
        {
            home.get_sencor(2).on_off(_on);
        }
        if(ui->c_water->isChecked())
        {
            home.get_sencor(3).on_off(_on);
        }
        user.delete_house(home);
        user.in_vector(home);
        user.save_all();
        par->obnov(user.get_login(),user.get_pass(),user.get_adm(),user.get_money());
        ui->warning->setStyleSheet("QLabel {background-color:rgb(32, 180, 28);color: rgb(238, 238, 236);}");
        ui->warning->setText("\t\t\t\t\t\t\tИзменения успешны.");
        obnov();
    }
}
/*!
 * \brief Метод класса work_counter, отвечающий за выключение счетчика.
 */
void work_counter::on_on_false_clicked()
{
    bool _on=false;
    if (!(ui->c_elecrt->isChecked() || ui->c_gas->isChecked() || ui->c_water->isChecked()))
    {
        ui->warning->setStyleSheet("QLabel {background-color: rgba(204, 0, 0,1)");
        ui->warning->clear();
        return;
    }
    if((ui->c_elecrt->isChecked() && !(home.get_sencor(1).get_have())) || (ui->c_gas->isChecked() && !(home.get_sencor(2).get_have())) \
      ||   (ui->c_water->isChecked() && !(home.get_sencor(3).get_have())))
    {
        ui->warning->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
        ui->warning->setText("\t\t\t\t\t\tНельзя выключить не установленный счетчик.");
        return;
    }
    if((ui->c_elecrt->isChecked() && !home.get_sencor(1).get_on()) || (ui->c_gas->isChecked() && !home.get_sencor(2).get_on()) \
            || (ui->c_water->isChecked() && !home.get_sencor(3).get_on()))
    {
        ui->warning->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
        ui->warning->setText("\t\t\t\t\t\tНельзя выключить выключенный счетчик.");
    }
    else
    {
        if(ui->c_elecrt->isChecked())
        {
            home.get_sencor(1).on_off(_on);
            home.off_devais(1);
        }
        if(ui->c_gas->isChecked())
        {
            home.get_sencor(2).on_off(_on);
            home.off_devais(2);
        }
        if(ui->c_water->isChecked())
        {
            home.get_sencor(3).on_off(_on);
            home.off_devais(3);
        }
        user.delete_house(home);
        user.in_vector(home);
        user.save_all();
        par->obnov(user.get_login(),user.get_pass(),user.get_adm(),user.get_money());
        ui->warning->setStyleSheet("QLabel {background-color:rgb(32, 180, 28);color: rgb(238, 238, 236);}");
        ui->warning->setText("\t\t\t\t\t\t\tИзменения успешны.");
        obnov();
    }
}
/*!
 * \brief Метод класса work_counter, отвечающий за установку счетчика.
 */
void work_counter::on_have_true_clicked()
{
    bool _on=true;
    double proc =0;
    if (!(ui->c_elecrt->isChecked() || ui->c_gas->isChecked() || ui->c_water->isChecked()))
    {
        ui->warning->setStyleSheet("QLabel {background-color: rgba(204, 0, 0,1)");
        ui->warning->clear();
        return;
    }
    if((ui->c_elecrt->isChecked() && home.get_sencor(1).get_have()) || (ui->c_gas->isChecked() && home.get_sencor(2).get_have()) \
      ||   (ui->c_water->isChecked() && home.get_sencor(3).get_have()))
    {
        ui->warning->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
        ui->warning->setText("\t\t\t\t\t\tНельзя установить установленный счетчик.");
        return;
    }
    else
    {
        if(ui->c_elecrt->isChecked())
        {
            home.get_sencor(1).on_off(_on);
            home.get_sencor(1).put_sencor(_on,_on,proc);
        }
        if(ui->c_gas->isChecked())
        {
            home.get_sencor(2).on_off(_on);
            home.get_sencor(2).put_sencor(_on,_on,proc);
        }
        if(ui->c_water->isChecked())
        {
            home.get_sencor(3).on_off(_on);
            home.get_sencor(3).put_sencor(_on,_on,proc);
        }
        user.delete_house(home);
        user.in_vector(home);
        user.save_all();
        par->obnov(user.get_login(),user.get_pass(),user.get_adm(),user.get_money());
        ui->warning->setStyleSheet("QLabel {background-color:rgb(32, 180, 28);color: rgb(238, 238, 236);}");
        ui->warning->setText("\t\t\t\t\t\t\tИзменения успешны.");
        obnov();
    }
}
/*!
 * \brief Метод класса work_counter, отвечающий за демонтаж счетчика.
 */
void work_counter::on_have_false_clicked()
{
    bool _on=false;
    double proc =0;
    if (!(ui->c_elecrt->isChecked() || ui->c_gas->isChecked() || ui->c_water->isChecked()))
    {
        ui->warning->setStyleSheet("QLabel {background-color: rgba(204, 0, 0,1)");
        ui->warning->clear();
        return;
    }
    if((ui->c_elecrt->isChecked() && !home.get_sencor(1).get_have()) || (ui->c_gas->isChecked() && !home.get_sencor(2).get_have()) \
      ||   (ui->c_water->isChecked() && !home.get_sencor(3).get_have()))
    {
        ui->warning->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
        ui->warning->setText("\t\t\t\t\tНельзя демонтировать не установленный счетчик.");
        return;
    }
    else
    {
        if(ui->c_elecrt->isChecked())
        {
            home.get_sencor(1).put_sencor(_on,_on,proc);
            home.off_devais(1);
        }
        if(ui->c_gas->isChecked())
        {
            home.get_sencor(2).put_sencor(_on,_on,proc);
            home.off_devais(2);
        }
        if(ui->c_water->isChecked())
        {
            home.get_sencor(3).put_sencor(_on,_on,proc);
            home.off_devais(3);
        }
        user.delete_house(home);
        user.in_vector(home);
        user.save_all();
        par->obnov(user.get_login(),user.get_pass(),user.get_adm(),user.get_money());
        ui->warning->setStyleSheet("QLabel {background-color:rgb(32, 180, 28);color: rgb(238, 238, 236);}");
        ui->warning->setText("\t\t\t\t\t\t\tИзменения успешны.");
        obnov();
    }
}
/*!
 * \brief Метод класса work_counter, отвечающий за починку счетчика.
 */
void work_counter::on_norm_true_clicked()
{
    bool _on=true;
    double proc =0;
    if (!(ui->c_elecrt->isChecked() || ui->c_gas->isChecked() || ui->c_water->isChecked()))
    {
        ui->warning->setStyleSheet("QLabel {background-color: rgba(204, 0, 0,1)");
        ui->warning->clear();
        return;
    }
    if((ui->c_elecrt->isChecked() && !(home.get_sencor(1).get_have())) || (ui->c_gas->isChecked() && !(home.get_sencor(2).get_have())) \
      ||   (ui->c_water->isChecked() && !(home.get_sencor(3).get_have())))
    {
        ui->warning->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
        ui->warning->setText("\t\t\t\t\t\tНельзя починить не установленный счетчик.");
        return;
    }
    if((ui->c_elecrt->isChecked() && home.get_sencor(1).get_norm()) || (ui->c_gas->isChecked() && home.get_sencor(2).get_norm()) || \
       (ui->c_water->isChecked() && home.get_sencor(3).get_norm()))
    {
        ui->warning->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
        ui->warning->setText("\t\t\t\tНельзя починить нормальнофункционирующий счетчик.");
    }
    else
    {
        if(ui->c_elecrt->isChecked())
        {
            home.get_sencor(1).put_sencor(_on,_on,proc);
        }
        if(ui->c_gas->isChecked())
        {
            home.get_sencor(2).put_sencor(_on,_on,proc);
        }
        if(ui->c_water->isChecked())
        {
            home.get_sencor(3).put_sencor(_on,_on,proc);
        }
        user.delete_house(home);
        user.in_vector(home);
        user.save_all();
        par->obnov(user.get_login(),user.get_pass(),user.get_adm(),user.get_money());
        ui->warning->setStyleSheet("QLabel {background-color:rgb(32, 180, 28);color: rgb(238, 238, 236);}");
        ui->warning->setText("\t\t\t\t\t\t\tИзменения успешны.");
        obnov();
    }
}
/*!
 * \brief Метод класса work_counter, отвечающий за ломку счетчика.
 */
void work_counter::on_norm_false_clicked()
{
    bool _on=false;
    double proc =0;
    bool help=true;
    if (!(ui->c_elecrt->isChecked() || ui->c_gas->isChecked() || ui->c_water->isChecked()))
    {
        ui->warning->setStyleSheet("QLabel {background-color: rgba(204, 0, 0,1)");
        ui->warning->clear();
        return;
    }
    if((ui->c_elecrt->isChecked() && !(home.get_sencor(1).get_have())) || (ui->c_gas->isChecked() && !(home.get_sencor(2).get_have())) \
      ||   (ui->c_water->isChecked() && !(home.get_sencor(3).get_have())))
    {
        ui->warning->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
        ui->warning->setText("\t\t\t\t\t\tНельзя сломать не установленный счетчик.");
        return;
    }
    if((ui->c_elecrt->isChecked() && !home.get_sencor(1).get_norm()) || (ui->c_gas->isChecked() && !home.get_sencor(2).get_norm()) || \
       (ui->c_water->isChecked() && !home.get_sencor(3).get_norm()))
    {
        ui->warning->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
        ui->warning->setText("\t\t\t\t\t\tНельзя сломать сломанный счетчик.");
    }
    else
    {
        if(ui->c_elecrt->isChecked())
        {
            home.get_sencor(1).put_sencor(help,_on,proc);
            home.off_devais(1);

        }
        if(ui->c_gas->isChecked())
        {
            home.get_sencor(2).put_sencor(help,_on,proc);
            home.off_devais(2);

        }
        if(ui->c_water->isChecked())
        {
            home.get_sencor(3).put_sencor(help,_on,proc);
            home.off_devais(3);

        }
        user.delete_house(home);
        user.in_vector(home);
        user.save_all();
        par->obnov(user.get_login(),user.get_pass(),user.get_adm(),user.get_money());
        ui->warning->setStyleSheet("QLabel {background-color:rgb(32, 180, 28);color: rgb(238, 238, 236);}");
        ui->warning->setText("\t\t\t\t\t\t\tИзменения успешны.");
        obnov();
    }
}
