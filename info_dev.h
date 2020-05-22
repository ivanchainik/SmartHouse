/*!
  \file
  \brief Данный файл содержит описание класса info_dev.
*/
#ifndef INFO_DEV_H
#define INFO_DEV_H

#include <QWidget>
#include "work_dev.h"

namespace Ui {
class info_dev;
}

/*!
 * \brief Класс отвечающий за графический интерфейс вывода информации по девайсу.
 */
class info_dev : public QWidget
{
    Q_OBJECT

public:
    explicit info_dev(house &_home,room &_komn,devais &_dev,work_dev *parent);
    ~info_dev();

private slots:
    void on_back_clicked();

private:
    Ui::info_dev *ui;
    work_dev *par;
};

#endif // INFO_DEV_H
