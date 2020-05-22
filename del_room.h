/*!
  \file
  \brief Данный файл содержит описание класса del_room.
*/
#ifndef DEL_ROOM_H
#define DEL_ROOM_H

#include <QWidget>
#include "mainmenu.h"
#include <string>
namespace Ui {
class del_room;
}

/*!
 * \brief Класс отвечающий за графический интерфейс удаления комнаты.
 */
class del_room : public QWidget
{
    Q_OBJECT

public:
    explicit del_room(account &_user,std::string &_adress,mainmenu *parent);
    ~del_room();

private slots:
    void on_back_clicked();

    void on_delet_clicked();

private:
    account user;///< Аккаунт, в котором происходит изменение.
    Ui::del_room *ui;///< Графический интерфейс класса add_cond.
    mainmenu *batya;///< Указатель на класс родитель.
    std::string adress;///< Адресс дома, в котором находится комната.
    void obnova();
};

#endif // DEL_ROOM_H
