/*!
\file
\brief Заголовочный файл с описанием класса add_room.
  */
#ifndef ADD_ROOM_H
#define ADD_ROOM_H
#include "house.h"
#include <QWidget>
#include "account.h"
#include "mainmenu.h"

namespace Ui {
class add_room;
}
/*!
 * \brief Класс, отвечающий за графический интерфейс добавления комнаты.
 */
class add_room : public QWidget
{
    Q_OBJECT

public:
    explicit add_room(account &a,house &dom,int &_numberofroom,int &allroom,mainmenu *parent = 0);
    ~add_room();

private slots:
    void on_enter_clicked();

private:
    Ui::add_room *ui;///< Графический интерфейс добавления комнаты.
    int num;///< Номер комнаты, которую нужно добавить.
    int allnum;///< Общее количество комнат в доме.
    mainmenu *par;///< Указатель на класс родитель.
    account auser;///< Аккаунт, в котором происходит изменения.
    house home;///< Дом в котором происходит изменения.
};

#endif // ADD_ROOM_H
