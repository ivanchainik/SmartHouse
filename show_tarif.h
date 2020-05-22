/*!
  \file
  \brief Файл,содержащий  класс show_tarif.
  */
#ifndef SHOW_TARIF_H
#define SHOW_TARIF_H
#include"tarif.h"

#include <QWidget>

namespace Ui {
class show_tarif;
}
/*!
 * \brief Класс,отвечающий за вывод данных о тарифах.
 */
class show_tarif : public QWidget
{
    Q_OBJECT

public:
    explicit show_tarif(QWidget *parent = 0);
    ~show_tarif();

private slots:
    void on_back_clicked();

private:
    Ui::show_tarif *ui;///<Графический интерфейс класса show_tarif.
};

#endif // SHOW_TARIF_H
