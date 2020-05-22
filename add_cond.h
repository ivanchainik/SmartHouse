/*!
  \file
  \brief Данный файл содержит описание класса add_cond
  */
#ifndef ADD_COND_H
#define ADD_COND_H

#include <QWidget>
#include "work_sen.h"
namespace Ui {
class add_cond;
}
/*!
 * \brief Класс ,отвечающий за графический интерфейс подключения кондиционера.
 */
class add_cond : public QWidget
{
    Q_OBJECT

public:
    explicit add_cond(house &a,room &b,work_sen *parent);
    ~add_cond();

private slots:
    void on_back_clicked();

    void on_enter_clicked();

private:
    Ui::add_cond *ui;///<Графический интерфейс класса add_cond.
    house dom;///<Дом, в котором происходят изменения.
    room komn;///<Комната, в которой происходят изменения.
    work_sen *par;///<Указатель на класс родитель.
};

#endif // ADD_COND_H
