/*!
\file
\brief Исходный файл, содержащий описание класса chang_house.
*/
#include "chang_house.h"
#include "ui_chang_house.h"
#include "house.h"
#include <vector>
/*!
 * \brief Конструктор класса chang_house.
 * \param azer Аккаунт, в котором происходит изменение.
 * \param str Адресс редактируемого дома.
 * \param parent Указатель на класс родитель.
 */
Chang_house::Chang_house(account &azer,std::string &str,mainmenu *parent) :
    QWidget(parent),
    ui(new Ui::Chang_house)
{
    ui->setupUi(this);
    user=azer;
    par=parent;
    adress=str;
    user.delete_all_house();
    obnov();
    setWindowTitle("\"Умный дом\":Редактирование дома.");
    QPixmap pix(":/picha/Pichures/chang_house.png");

}
/*!
 * \brief Деструктор класса chang_house.
 */
Chang_house::~Chang_house()
{
    delete ui;
}
/*!
 * \brief Метод класса chang_house, отвечающий за обновлении окна.
 */
void Chang_house::obnov()
{
    user.read_all();
    std::vector<house> a=user.get_homes();
    std::vector<house>::iterator first=a.begin();
    std::vector<house>::iterator last=a.end();
    for(;first!=last;first++)
    {
        if(first->full_adress()==adress)
        {
            break;
        }
    }
    home=*first;
    ui->flatline->setText(QString("%1").arg(first->get_flat()));
    ui->numline->setText(QString("%1").arg(first->get_num()));
    ui->ownerline->setText(QString::fromStdString(first->get_owner()));
    ui->streetline->setText(QString::fromStdString(first->get_street()));
}
/*!
 * \brief Метод класса chang_house, отвечающий за редактирования дома.
 */
void Chang_house::on_Enter_clicked()
{
   bool warn=false;
   bool warn1;
   std::ifstream file;
   int k;
   char *str;
   double m;
   house dom;

   file.open("logins.dat",std::ios_base::binary);
   while(1)
  {
          file.read((char*)&k,sizeof(int));
          str=new char[k+1];
          file.read((char*)str,sizeof(char)*k);
          strcat(str,"\0");
          if(file.eof())
          {
              warn=true;
              delete []str;
              ui->warning->setStyleSheet("QLabel {background-color: rgb(204, 0, 0);color: rgb(238, 238, 236);}");
              ui->warning->setText(" Данного пользователя не существует.");
              break;
          }
          else if(!strcmp(str,ui->ownerline->text().toStdString().c_str()))
          {
              delete []str;
              ui->warning->setStyleSheet("QLabel {background-color:transparent}");
              ui->warning->clear();
              break;
          }
          delete []str;
          file.read((char*)&k,sizeof(int));
          str=new char[k];
          file.read((char*)str,sizeof(char)*k);
          delete []str;
          file.read((char*)&k,sizeof(int));
          file.read((char*)&m,sizeof(double));
   }
   file.close();
   ui->flatline->text().toInt(&warn1);
   if(warn1==false)
   {
       warn=true;
       ui->warning_4->setStyleSheet("QLabel {background-color: rgb(204, 0, 0);color: rgb(238, 238, 236);}");
       ui->warning_4->setText("Требовалось ввести целое число.");
   }
   else if(ui->flatline->text().toInt()<=0)
   {
       warn=true;
       ui->warning_4->setStyleSheet("QLabel {background-color: rgb(204, 0, 0);color: rgb(238, 238, 236)}");
       ui->warning_4->setText("Номер квартиры должен быть больше нуля.");
   }
   else
   {
       ui->warning_4->setStyleSheet("QLabel {background-color:transparent}");
       ui->warning_4->clear();
   }
   ui->numline->text().toInt(&warn1);
   if(warn1==false)
   {
       warn=true;
       ui->warning_3->setStyleSheet("QLabel {background-color: rgb(204, 0, 0);color: rgb(238, 238, 236);}");
       ui->warning_3->setText("Требовалось ввести целое число.");
   }
   else if(ui->numline->text().toInt()<=0)
   {
       warn=true;
       ui->warning_3->setStyleSheet("QLabel {background-color: rgb(204, 0, 0);color: rgb(238, 238, 236);}");
       ui->warning_3->setText("Номер дома должен быть больше нуля.");
   }
   else
   {
       ui->warning_3->setStyleSheet("QLabel {background-color:transparent}");
       ui->warning_3->clear();
   }
   if(warn !=true)
   {
       int _flat=ui->flatline->text().toInt();
       std::string _street =ui->streetline->text().toStdString();
       std::string _owner=ui->ownerline->text().toStdString();
       int _num=ui->numline->text().toInt();
       dom.put_house(_flat,_street,_owner,_num);
       std::vector<house> a=user.get_homes();
       std::vector<house>::iterator first=a.begin();
       std::vector<house>::iterator last=a.end();
       for(;first!=last;first++)
       {

           if(first->full_adress()==dom.full_adress() && !(dom.full_adress()==adress))
           {
               warn=true;
               ui->warning_4->setStyleSheet("QLabel {background-color: rgb(204, 0, 0);color: rgb(238, 238, 236);}");
               ui->warning_4->setText("Квартира с таким адресом уже существует.");
               break;
           }
       }
   }
   if(warn !=true)
   {
       user.delete_house(home);
       int _flat=ui->flatline->text().toInt();
       std::string _street =ui->streetline->text().toStdString();
       std::string _owner=ui->ownerline->text().toStdString();
       int _num=ui->numline->text().toInt();
       home.put_house(_flat,_street,_owner,_num);
       adress=home.full_adress();
       user.in_vector(home);
       user.save_all();
       ui->warning_4->setStyleSheet("QLabel{background-color:rgb(32, 180, 28);color: rgb(238, 238, 236);}");
       ui->warning_4->setText("\tИзменения успешны.");
       par->obnov(user.get_login(),user.get_pass(),user.get_adm(),user.get_money());
   }
}
/*!
 * \brief Метод класса chang_house,отвечающий за выход из окна.
 */
void Chang_house::on_back_clicked()
{
   delete this;
}
