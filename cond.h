/*!
  \file
  \brief Файл,содержащий класс cond.
  */
#ifndef COND_H
#define COND_H

#include <QWidget>
#include "house.h"
#include "work_sen.h"
namespace Ui {
class cond;
}
/*!
 * \brief Класс, отвечающий за включение кондиционера.
 */
class cond : public QWidget
{
    Q_OBJECT

public:
    explicit cond(house &_dom,room &_komn,work_sen *parent);
    ~cond();

private slots:
    void on_enter_clicked();

    void on_back_clicked();

private:
    Ui::cond *ui;///<Графический интерфейс включения кондиционера.
    house dom;///<Дом, в котором включают кондиционер.
    room komn;///<Комната, в которой включают кондиционер.
    work_sen *par;///<Указатель на родительский класс.
};

#endif // COND_H
