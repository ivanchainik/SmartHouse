/*!
\file
\brief Заголовочный файл с описанием класса chang_house.
  */
#ifndef CHANG_HOUSE_H
#define CHANG_HOUSE_H
#include "mainmenu.h"
#include <QWidget>

namespace Ui {
class Chang_house;
}
/*!
 * \brief Класс, отвечающий за графический интерфейс редактирования дома.
 */
class Chang_house : public QWidget
{
    Q_OBJECT

public:
    explicit Chang_house(account &azer,std::string &str,mainmenu *parent);
    ~Chang_house();

private slots:
    void on_Enter_clicked();

    void on_back_clicked();

private:
    Ui::Chang_house *ui;///< Графический интерфейс редактирования дома.
    account user;///< Аккаунт, в котором происходит изменение.
    mainmenu *par;///< Указатель на класс родитель.
    std::string adress;///< Адресс редактируемого дома.
    house home;///< Дом, который нужно редактировать.
    void obnov();
};

#endif // CHANG_HOUSE_H
