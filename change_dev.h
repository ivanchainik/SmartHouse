/*!
\file
\brief Заголовочный файл с описанием класса change_dev.
*/
#ifndef CHANGE_DEV_H
#define CHANGE_DEV_H

#include <QWidget>
#include "work_dev.h"
#include "devais.h"
#include "room.h"
namespace Ui {
class change_dev;
}
/*!
 * \brief Класс, отвечающий за графический интерфейс редактирования девайсов.
 */
class change_dev : public QWidget
{
    Q_OBJECT

public:
    explicit change_dev(house &_home,room &_komn,devais &_dev,work_dev *parent);
    ~change_dev();

private slots:
    void on_back_clicked();

    void on_enter_clicked();

private:
    Ui::change_dev *ui;///< Графический интерфейс редактирования девайсов.
    room komn;///< Комната, в которой происходит изменение.
    devais dev;///< Девайс, который нужно отредактировать.
    work_dev *par;///< Указатель на класс родитель.
    house home;/// Дом, в котором происходит изменение.
};

#endif // CHANGE_DEV_H
