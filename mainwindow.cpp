#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextEdit>
#include "insertrecipe.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = new DataBase();
    db->connectToDataBase();

    sqlDb= QSqlDatabase::addDatabase("QSQLITE");
    sqlDb.setDatabaseName("C:\\example\\"+db->getDataBaseName());
\
    loadDataBase();
    myInsertRecipe=new InsertRecipe();
    connect(ui->pushButton, SIGNAL(clicked()), myInsertRecipe, SLOT(show()));
}



void MainWindow::loadDataBase(){
   sqlDb.open();

   //Осуществляем запрос
   QSqlQuery query;
   query.exec("SELECT Name, Country, Kind, Photo FROM TableExample");

   //Выводим значения из запроса
   while (query.next())
   {
   QString name = query.value(0).toString();
   QString country = query.value(1).toString();
   QString kind = query.value(2).toString();
   QString photo = query.value(3).toString();

   ui->textEdit->insertPlainText(name+" "+country+" "+ kind+" "+ photo+"\n");
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
