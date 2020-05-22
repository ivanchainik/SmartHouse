/*!
\file
\brief Заголовочный файл с описанием класса chang_room.
*/
#ifndef CHANG_ROOM_H
#define CHANG_ROOM_H

#include <QWidget>
#include "mainmenu.h"

namespace Ui {
class Chang_room;
}
/*!
 * \brief Класс, отвечающий за графический интерфейс редактирования комнаты.
 */
class Chang_room : public QWidget
{
    Q_OBJECT

public:
    explicit Chang_room(const account &auser,std::string &_adress,mainmenu *parent = 0);
    ~Chang_room();

private slots:
    void on_rooms_itemSelectionChanged();

    void on_Enter_clicked();

    void on_back_clicked();

private:
    Ui::Chang_room *ui;///< Графический интерфейс редактирования комнаты.
    account user;///< Аккаунт, в котором происходит изменение.
    mainmenu *par;///< Указатель на класс родитель.
    std::string adress;///< Адресс дома, в котором находится комната.
    void obnova();
    house home;///< Дом, в котором происходит изменение.


};

#endif // CHANG_ROOM_H
