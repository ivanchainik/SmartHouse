/*!
  \file
  \brief Файл ,содержащий класс change_pass.
*/
#ifndef CHANGE_PASS_H
#define CHANGE_PASS_H

#include <QWidget>
#include "account.h"
#include "mainmenu.h"

namespace Ui {
class change_pass;
}
/*!
 * \brief Класс ,отвечающий за окно смены пароля.
 */
class change_pass : public QWidget
{
    Q_OBJECT

public:
    explicit change_pass(account &user,mainmenu *parent = 0);
    ~change_pass();

private slots:
    void on_back_clicked();

    void on_pushButton_clicked();

private:
    Ui::change_pass *ui;///<Графический интерфейс класса change_pass.
    account user1;///<Аккаунт ,в котором меняем пароль.
    mainmenu *a;///<Указатель на родительский класс.
};

#endif // CHANGE_PASS_H
