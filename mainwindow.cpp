#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextEdit>
#include "insertrecipe.h"

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
   query.exec("SELECT Name, Country, Kind FROM TableExample");

   //Выводим значения из запроса
   while (query.next())
   {
   QString name = query.value(0).toString();
   QString country = query.value(1).toString();
   QString kind = query.value(2).toString();

   ui->textEdit->insertPlainText(name+" "+country+" "+ kind+ "\n");
   }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::on_pushButton_2_clicked()
{
    ui->textEdit->clear();
    loadDataBase();
}
