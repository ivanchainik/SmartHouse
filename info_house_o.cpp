/*!
\file
\brief Исходный файл, содержащий описание методов класса info_dev.
*/
#include "info_house_o.h"
#include "ui_info_house_o.h"

/*!
 * \brief Конструктор класса info_house_o.
 * \param a Передаёт наименование дома.
 * \param parent Передаёт ссылку на родителя.
 */
info_house_o::info_house_o(house &a,mainmenu *parent) :
    QWidget(parent),
    ui(new Ui::info_house_o)
{

    ui->setupUi(this);
    ui->_street->setText(QString::fromStdString(a.get_street()));
    ui->_flat->setText(QString("%1").arg(a.get_flat()));
    ui->_area->setText(QString("%2").arg(a.all_area()));
    ui->_num->setText(QString("%1").arg(a.get_num()));
    ui->_value->setText(QString("%1").arg(a.get_lives().size()));
    ui->_owner->setText(QString::fromStdString(a.get_owner()));
    setWindowTitle("\"Умный дом\":Информация о доме.");
    QPixmap pix(":/picha/Pichures/info_house_o.png");
}
/*!
 * \brief Деструктор класса info_house_o.
 */
info_house_o::~info_house_o()
{
    delete ui;
}
/*!
 * \brief Выводлит информацию о доме на экран.
 */
void info_house_o::on_pushButton_clicked()
{
    delete this;
}
