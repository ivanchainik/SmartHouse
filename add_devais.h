/*!
\file
\brief Заголовочный файл с описанием класса add_devais.
*/
#ifndef ADD_DEVAIS_H
#define ADD_DEVAIS_H
#include <QWidget>
#include "work_dev.h"
namespace Ui {
class add_devais;
}
/*!
 * \brief Класс, отвечающий за графический интерфейс подключения девайса.
 */
class add_devais : public QWidget
{
    Q_OBJECT

public:
    explicit add_devais(account &a,const house &_home,const room &_komn,work_dev *parent);
    ~add_devais();

private slots:
    void on_back_clicked();

    void on_enter_clicked();

private:
    Ui::add_devais *ui;///< Графический интерфейс класса add_devais.
    work_dev *par;///< Указатель на класс родитель.
    account user;///< Аккаунт, в котором происходит изменения.
    house dom;///< Дом, в котором происходит изменения.
    room komn;///< Комната, в которой происходит изменения.
};

#endif // ADD_DEVAIS_H
