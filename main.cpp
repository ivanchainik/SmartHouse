/*!
\file
\brief Исходный файл, содержащий функцию main.
*/
#include "menu.h"
#include <QApplication>

/*!
 * \brief Функция main.
 *
 * Создаёт обьект класса menu, и запускает графический интерфейс.
 * \return 0 - при удачном заверщении работы.
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    menu *w=new menu;
    w->show();
    return a.exec();
}
