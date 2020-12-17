#include "insertrecipe.h"
#include "ui_insertrecipe.h"
#include "database.h"
#include "mainwindow.h"
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>


InsertRecipe::InsertRecipe(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InsertRecipe)
{
    ui->setupUi(this);
    this->setWindowTitle("Добавить рецепт");
}

InsertRecipe::~InsertRecipe()
{
    delete ui;
}

void InsertRecipe::on_pushButton_clicked()
{
    while(ui->lineEdit->text().isEmpty()||ui->textEdit->toPlainText().isEmpty()||ui->lineEdit_3->text().isEmpty()){
        QMessageBox::warning(this, "Внимание","Заполните все необходимые поля");
        return;
    }
     DataBase *db;
    QVariantList data;
    data.append(QDate::currentDate()); // Получаем текущую дату для вставки в БД
    if(filename.isEmpty())
        data.append("null");
    else
    data.append(filename);
    data.append(ui->lineEdit->text());
    data.append(false);
    data.append(false);
    data.append(ui->textEdit->toPlainText());
    data.append(ui->lineEdit_3->text());
    data.append(ui->comboBox->currentText());
    data.append(ui->lineEdit_4->text());
    data.append(ui->lineEdit_6->text());
    data.append(ui->comboBox_2->currentText());
    db->inserIntoTable(data);
    close();
 }

void InsertRecipe::on_pushButton_2_clicked()
{
        filename = QFileDialog::getOpenFileName(0,"Выберите изображение", QDir::currentPath(),"*.png *.jpg *.gif *.jpeg");
        QImage image1(filename);
        ui->label_16->setPixmap((QPixmap::fromImage(image1)).scaled(200,200,Qt::KeepAspectRatio));
}
