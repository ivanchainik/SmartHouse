/*!
  \file
  \brief Файл ,содержащий класс  mainmenu.
  */
#ifndef MAINMENU_H
#define MAINMENU_H
#include<string>
#include<QWidget>
#include"account.h"
#include"tarif.h"
namespace Ui {
class mainmenu;
}
/*!
 * \brief Класс ,содержащий основное меню программы.
 */
class mainmenu : public QWidget
{
    Q_OBJECT

public:
    explicit mainmenu(const std::string &_login,const std::string &_pass,const bool &_adm,const double &_money,QWidget *parent = 0);
    void obnov(const std::string &_login,const std::string &_pass,const bool &_adm,const double &_money);
    ~mainmenu();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_Changetar_clicked();

    void on_change_pass_clicked();

    void on_Changetar_2_clicked();

    void on_Newhouse_clicked();

    void on_delete_house_clicked();

    void on_delacc_clicked();

    void on_add_room_clicked();

    void on_info_house_clicked();

    void on_dele_room_clicked();

    void on_Change_h_clicked();

    void on_chang_room_clicked();

    void on_Countet_butt_clicked();

    void on_Devais_butt_clicked();

    void on_Sencor_butt_clicked();

    void on_bank_clicked();

private:
    Ui::mainmenu *ui;///<Графический интерфейс класса add_cond.
    account user;///<Пользователь.
    void plus_house();
};

#endif // MAINMENU_H
