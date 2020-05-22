/*!
  \file
  \brief Файл ,содержащий класс change_tarife.
  */
#ifndef CHANGE_TARIFE_H
#define CHANGE_TARIFE_H

#include <QWidget>

namespace Ui {
class change_tarife;
}
/*!
 * \brief Класс ,отвечающий за окно редактирования тарифов.
 */
class change_tarife : public QWidget
{
    Q_OBJECT

public:
    explicit change_tarife(QWidget *parent = 0);
    ~change_tarife();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::change_tarife *ui;///<Графический интерфейс класса add_cond.
};

#endif // CHANGE_TARIFE_H
