/*!
  \brief Файл ,содержащий класс menu.
  */
#ifndef MENU_H
#define MENU_H

#include <QMainWindow>

namespace Ui {
class menu;
}
/*!
 * \brief Класс,отвечающий за авторизацию.
 */
class menu : public QMainWindow
{
    Q_OBJECT

public:
    explicit menu(QWidget *parent = 0);
    ~menu();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_lineEdit_selectionChanged();

    void on_lineEdit_2_selectionChanged();

private:
    Ui::menu *ui;///<Графический интерфейс класса menu.
    bool fl;///<Флаг логина.
    bool fl2;///<Флаг пароля.
};

#endif // MENU_H
