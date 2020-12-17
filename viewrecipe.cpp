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

    //Осуществляем запрос
    QSqlQuery query;
    query.exec("SELECT * FROM TableExample WHERE id="+id);

    //Выводим значения из запроса
    while (query.next())
    {
    QString date = query.value(1).toString();
    QImage image(query.value(2).toString());
    this->setWindowTitle(query.value(3).toString());
    bool Like = query.value(4).toBool();
    bool Was = query.value(5).toBool();
    QString recipe = query.value(6).toString();
    QString ingredients = query.value(7).toString();
    QString kind = query.value(8).toString();
    QString country = query.value(9).toString();
    QString time = query.value(10).toString();
    QString complexity = query.value(11).toString();

    ui->label->setPixmap(QPixmap::fromImage(image).scaled(200,200,Qt::KeepAspectRatio));
    ui->checkBox->setChecked(Like);
    ui->checkBox_2->setChecked(Was);
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

void viewRecipe::on_pushButton_2_clicked()
{
    QSqlQuery query;
    query.prepare("UPDATE TableExample SET Like = :text WHERE id = :id");
    query.bindValue(":id", id);
    query.bindValue(":text", ui->checkBox->isChecked());
    if(!query.exec()){
        qDebug() << "error update  " << TABLE;
        qDebug() << query.lastError().text();
    }

    QSqlQuery query2;
    query.prepare("UPDATE TableExample SET Was = :text WHERE id = :id");
    query.bindValue(":id", id);
    query.bindValue(":text", ui->checkBox_2->isChecked());
    if(!query.exec()){
        qDebug() << "error update  " << TABLE;
        qDebug() << query.lastError().text();
    }
 close();
}

