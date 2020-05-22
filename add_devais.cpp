/*!
\file
\brief Исходный файл, содержащий описание методов класса add_devais.
*/
#include "add_devais.h"
#include "ui_add_devais.h"
#include "work_dev.h"
/*!
 * \brief Конструктор класса add_devais.
 * \param a Аккаунт, в котором происходит изменения.
 * \param _home Дом, в котором происходит изменения.
 * \param _komn Комната, в котором происходит изменения.
 * \param parent Указатель на класс родитель.
 */
add_devais::add_devais(account &a,const house &_home,const room &_komn,work_dev *parent) :
    QWidget(0),
    ui(new Ui::add_devais)
{
    user=a;
    par=parent;
    par->close();
    dom=_home;
    komn=_komn;
    ui->setupUi(this);
    setWindowTitle("\"Умный дом\":Добавление прибора.");
    QPixmap pix(":/picha/Pichures/devais.png");
}
/*!
 * \brief Деструктор класса add_devais.
 */
add_devais::~add_devais()
{
    delete ui;
}
/*!
 * \brief Метод класса add_devais, отвечающий за выход из окна.
 */
void add_devais::on_back_clicked()
{
    par->show();
    delete this;
}
/*!
 * \brief Метод класса add_devais, отвечающий за создание девайса.
 */
void add_devais::on_enter_clicked()
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
            if(first->get_name()==name)
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
        devais one;
        one.put_devais(name);
        one.put_kom(1,komm[0]);
        one.put_kom(2,komm[1]);
        one.put_kom(3,komm[2]);
        _on=ui->checkBox->isChecked();
        if(_on==true && user.get_money()<=0)
        {
            ui->warning_4->setStyleSheet("QLabel {background-color:rgb(204, 0, 0);color: rgb(238, 238, 236);}");
            ui->warning_4->setText("У вас не достаточно денег.");
            return;
        }
        one.on_off(_on);
        user.push_devais(one,dom,komn);
        par->obnov();
        par->ok_new_dev();
        par->show();
        delete this;
    }
}
