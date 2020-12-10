#include "insertrecipe.h"
#include "ui_insertrecipe.h"
#include "database.h"
#include "mainwindow.h"

InsertRecipe::InsertRecipe(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InsertRecipe)
{
    ui->setupUi(this);

}

InsertRecipe::~InsertRecipe()
{
    delete ui;
}

void InsertRecipe::on_pushButton_clicked()
{
     DataBase        *db;
    QVariantList data;
    data.append(QDate::currentDate()); // Получаем текущую дату для вставки в БД
    data.append("ssssss");
    data.append(ui->lineEdit->text());
    data.append(false);
    data.append(false);
    data.append("Замороженные пельмени");
    data.append("Пельмени, вода, соль");
    data.append("основное блюдо");
    data.append("Россия");
    data.append(15);
    data.append(1);
    db->inserIntoTable(data);
 //   ui->textEdit->clear();
   // loadDataBase();
   // MainWindow.loadDataBase();
//    QSqlDatabase db2;
//    db2 = QSqlDatabase::addDatabase("QSQLITE");
//    db2.setDatabaseName("C:\\example\\DataBase.db");
//    db2.open();

//    //Осуществляем запрос
//    QSqlQuery query;
//    query.exec("SELECT Name, Country FROM TableExample");

//    //Выводим значения из запроса
//    while (query.next())
//    {
//    QString name = query.value(0).toString();
//    QString country = query.value(1).toString();
//    ui->textEdit->insertPlainText(name+" "+country+"\n");
    }
  // db->
           // ui->lineEdit->text()
