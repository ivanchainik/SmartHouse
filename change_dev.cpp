/*!
\file
\brief Исходный файл с описанием класса change_dev.
*/
#include "change_dev.h"
#include "ui_change_dev.h"
#include "work_dev.h"
/*!
 * \brief Конструктор класса change_dev.
 * \param _home Дом, в котором происходит изменение.
 * \param _komn Комната, в которой происходит изменение.
 * \param _dev Девайс, который нужно отредактировать.
 * \param parent Указатель на класс родителя.
 */
change_dev::change_dev(house &_home,room &_komn,devais &_dev,work_dev *parent) :
    QWidget(0),
    ui(new Ui::change_dev)
{
    ui->setupUi(this);
    dev=_dev;
    par=parent;
    komn=_komn;
    home=_home;
    par->close();
    setWindowTitle("\"Умный дом\":Редактирование девайса.");
    QPixmap pix(":/picha/Pichures/change_dev.png");
    ui->name->setText(QString::fromStdString(dev.get_name()));
    ui->electr->setText(QString("%1").arg(dev.get_electr()));
    ui->gas->setText(QString("%1").arg(dev.get_gas()));
    ui->water->setText(QString("%1").arg(dev.get_water()));
}
/*!
 * \brief Деструктор класса change_dev.
 */
change_dev::~change_dev()
{
    delete ui;
}
/*!
 * \brief Метод класса change_dev, отвечающий за выход из окна.
 */
void change_dev::on_back_clicked()
{
    par->show();
    par->obnov();
    delete this;
}
/*!
 * \brief Метод класса change_dev, отвечающий за редактирование девайса.
 */
void change_dev::on_enter_clicked()
{
    bool warn=false;
    std::string name=ui->name->text().toStdString();
    double komm [3];
    bool _on;

    if(name.size()==0)
    {
        warn=true;
        ui->warning->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
        ui->warning->setText("Название прибора не может быть пустым.");
    }
    else
    {
        std::vector<devais> all=komn.get_dev();
        for(std::vector<devais>::iterator first=all.begin();first != all.end();first++)
        {
            if(first->get_name()==name && first->get_name() != dev.get_name())
            {
                warn=true;
                ui->warning->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
                ui->warning->setText("Прибор с таким названием уже есть в данной комнате.");
            }
        }
    }
    if(warn==false)
    {
        ui->warning->setStyleSheet("(QLabel {background-color: rgba(204, 0, 0,1)");
        ui->warning->clear();
    }
    komm[0]=ui->electr->text().toDouble(&_on);
    if(_on !=true)
    {
          warn=true;
        ui->warning_2->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
        ui->warning_2->setText("Требовалось ввести число.");
    }
    else if(komm[0]<0)
    {
          warn=true;
        ui->warning_2->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
        ui->warning_2->setText("Потребление не может быть отритцательным.");
    }
    else
    {
        ui->warning_2->setStyleSheet("(QLabel {background-color: rgba(204, 0, 0,1)");
        ui->warning_2->clear();
    }

    komm[1]=ui->gas->text().toDouble(&_on);
    if(_on !=true)
    {
          warn=true;
        ui->warning_3->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
        ui->warning_3->setText("Требовалось ввести число.");
    }
    else if(komm[1]<0)
    {
          warn=true;
        ui->warning_3->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
        ui->warning_3->setText("Потребление не может быть отритцательным.");
    }
    else
    {
        ui->warning_3->setStyleSheet("(QLabel {background-color: rgba(204, 0, 0,1)");
        ui->warning_3->clear();
    }

    komm[2]=ui->water->text().toDouble(&_on);
    if(_on !=true)
    {
        warn=true;
        ui->warning_4->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
        ui->warning_4->setText("Требовалось ввести число.");
    }
    else if(komm[2]<0)
    {
         warn=true;
        ui->warning_4->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
        ui->warning_4->setText("Потребление не может быть отридцательным.");
    }
    else
    {
        ui->warning_4->setStyleSheet("(QLabel {background-color: rgba(204, 0, 0,1)");
        ui->warning_4->clear();
    }
    if(warn==false)
    {
        account user;
        user.delete_devais(home,komn,dev);
        user.delete_all_house();
        dev.put_devais(name);
        dev.put_kom(1,komm[0]);
        dev.put_kom(2,komm[1]);
        dev.put_kom(3,komm[2]);
        user.push_devais(dev,home,komn);
        par->obnov();
        ui->warning_5->setStyleSheet("QLabel {background-color:rgb(32, 180, 28);color: rgb(238, 238, 236);}");
        ui->warning_5->setText("Прибор успешно изменен.");
    }
    else
    {
        ui->warning_5->setStyleSheet("(QLabel {background-color: rgba(204, 0, 0,1)");
        ui->warning_5->clear();
    }
}
