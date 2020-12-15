#include "viewrecipe.h"
#include "ui_viewrecipe.h"
#include "database.h"

viewRecipe::viewRecipe(QString id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::viewRecipe)
{
    ui->setupUi(this);
    this->id=id;
    loadData();
   }

viewRecipe::~viewRecipe()
{
    delete ui;
}

void viewRecipe:: loadData(){
    setForm();
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:\\example\\DataBase.db");
    db.open();

    //Осуществляем запрос
    QSqlQuery query;
    query.exec("SELECT * FROM TableExample WHERE id="+id);

    //Выводим значения из запроса
    while (query.next())
    {
    QString date = query.value(1).toString();
    this->setWindowTitle(query.value(3).toString());
    QString recipe = query.value(6).toString();
    QString ingredients = query.value(7).toString();
    QString kind = query.value(8).toString();
    QString country = query.value(9).toString();
    QString time = query.value(10).toString();
    QString complexity = query.value(11).toString();

    ui->label_2->setText(date);
    ui->textEdit->insertPlainText(ingredients+" "+"\n");
    ui->textEdit_2->insertPlainText(recipe+" "+"\n");
    ui->label_9->setText(time);
    ui->label_10->setText(complexity);
    ui->label_11->setText(kind);
    ui->label_12->setText(country);
    }

}


void viewRecipe::setForm()
{
    ui->textEdit->setReadOnly(true);
    ui->textEdit_2->setReadOnly(true);
}

void viewRecipe::on_pushButton_clicked()
{
    close();
}
