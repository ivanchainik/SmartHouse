/*!
\file
\brief Заголовочный файл с описанием класса add_house.
*/
#ifndef ADD_HOUSE_H
#define ADD_HOUSE_H
#include <QWidget>
#include "account.h"
#include "house.h"
#include "mainmenu.h"
namespace Ui {
class Add_house;
}
/*!
 * \brief Класс, отвечающий за графический интерфейс добавления дома.
 */
class Add_house : public QWidget
{
    Q_OBJECT

public:
    explicit Add_house(account &_user,mainmenu *parent = 0);
    ~Add_house();

private slots:
    void on_back_clicked();

    void on_enter_clicked();

private:
    Ui::Add_house *ui;///< Графический интерфейс класса add_house.
    account user;///< Аккаунт, в котором происходит изменение.
    mainmenu *ParWin;///< Указатель на класс родитель.

};

#endif // ADD_HOUSE_H
