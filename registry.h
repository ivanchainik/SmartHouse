/*!
  \file
  \brief Файл, содержащий класс Registry.
  */
#ifndef REGISTRY_H
#define REGISTRY_H

#include <QWidget>
#include "account.h"

namespace Ui {
class Registry;
}
/*!
 * \brief Класс ,отвечающий за регистрацию пользователя.
 */
class Registry : public QWidget
{
    Q_OBJECT

public:
    explicit Registry(QWidget *parent = 0);
    ~Registry();

private slots:
    void on_go_clicked();

    void on_go_2_clicked();

    void on_Name_selectionChanged();

    void on_pass1_selectionChanged();

    void on_pass2_selectionChanged();

private:
    Ui::Registry *ui;///<Графический интерфейс класса Registry.
    bool fl1;///<Флаг ввода логина.
    bool fl2;///<Флаг ввода пароля.
    bool fl3;///<Флаг ввода повторного пароля.
};

#endif // REGISTRY_H
