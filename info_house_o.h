/*!
  \file
  \brief Данный файл содержит описание класса info_house_o.
*/
#ifndef INFO_HOUSE_O_H
#define INFO_HOUSE_O_H

#include <QWidget>
#include "mainmenu.h"
#include "house.h"
namespace Ui {
class info_house_o;
}
/*!
 * \brief Класс отвечающий за графический интерфейс вывода информации по девайсу.
 */
class info_house_o : public QWidget
{
    Q_OBJECT

public:
    explicit info_house_o(house &a,mainmenu *parent = 0);
    ~info_house_o();

private slots:
    void on_pushButton_clicked();

private:
    Ui::info_house_o *ui;
};

#endif // INFO_HOUSE_O_H
