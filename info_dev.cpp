/*!
\file
\brief Исходный файл, содержащий описание методов класса info_dev.
*/
#include "info_dev.h"
#include "ui_info_dev.h"
#include "work_dev.h"
/*!
 * \brief Коструктор класса info_dev.
 * \param _home Передаёт наименование дома, в которм находится девайс.
 * \param _komn Передаёт наименование комнаты, в которм находится девайс.
 * \param _dev Передаёт наименование девайса.
 * \param parent Передаёт ссылку на родителя.
 */
info_dev::info_dev(house &_home,room &_komn,devais &_dev,work_dev *parent) :
    QWidget(0),
    ui(new Ui::info_dev)
{
    par=parent;
    par->close();
    ui->setupUi(this);
    setWindowTitle("\"Умный дом\":Информация о приборе.");
    QPixmap pix(":/picha/Pichures/info_dev.png");
    ui->house->setText(QString::fromStdString(_home.full_adress()));
    ui->room->setText(QString::fromStdString(_komn.this_room()));
    ui->name->setText(QString::fromStdString(_dev.get_name()));
    ui->electr->setText(QString("%1").arg(_dev.get_electr()));
    ui->gas->setText(QString("%1").arg(_dev.get_gas()));
    ui->water->setText(QString("%1").arg(_dev.get_water()));
    if (_dev.get_on())
    {
        ui->on->setStyleSheet("QLabel {background-color:rgb(32, 180, 28);color: rgb(238, 238, 236);}");
        ui->on->setText("\t\t Прибор включен.");
    }
    else
    {
        ui->on->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
        ui->on->setText("\t\t Прибор выключен.");
    }
}
/*!
 * \brief Деструктор класса info_dev.
 */
info_dev::~info_dev()
{
    delete ui;
}
/*!
 * \brief Метод выводящий информацию по девайсу на экран.
 */
void info_dev::on_back_clicked()
{
    par->show();
    delete this;
}
