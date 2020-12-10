#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextEdit>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myInsertRecipe=new InsertRecipe();
    connect(ui->pushButton, SIGNAL(clicked()), myInsertRecipe, SLOT(show()));
    loadDataBase();
}


void MainWindow::loadDataBase(){
    //Подключаем базу данных
   QSqlDatabase db;
   db = QSqlDatabase::addDatabase("QSQLITE");
   db.setDatabaseName("C:\\example\\DataBase.db");
   db.open();

   //Осуществляем запрос
   QSqlQuery query;
   query.exec("SELECT Name, Country FROM TableExample");

   //Выводим значения из запроса
   while (query.next())
   {
   QString name = query.value(0).toString();
   QString country = query.value(1).toString();
   ui->textEdit->insertPlainText(name+" "+country+"\n");
   }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    for(int i = 0; i < 1; i++){
        QVariantList data;

        data.append(QDate::currentDate()); // Получаем текущую дату для вставки в БД
        data.append("ssilka");
        data.append("Meat");
        data.append(false);
        data.append(false);
        data.append("Замороженные пельмени");
        data.append("Пельмени, вода, соль");
        data.append("основное блюдо");
        data.append("Россия");
        data.append(15);
        data.append(1);
        db->inserIntoTable(data);
        ui->textEdit->clear();
        loadDataBase();

    }
}

