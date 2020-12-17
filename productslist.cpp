#include "productslist.h"
#include "ui_productslist.h"
#include<QFileDialog>
#include <QMessageBox>
#include <QTextEdit>
#include <QTextStream>
#include <QColorDialog>

ProductsList::ProductsList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProductsList)
{
    ui->setupUi(this);
    this->setWindowTitle("Список продуктов");
    fileName= "list.txt";
    slotLoad();
}

ProductsList::~ProductsList()
{
    delete ui;
}

void ProductsList::on_pushButton_clicked()
{
    close();
}

void ProductsList::on_pushButton_2_clicked()
{
    slotSave();
}

void ProductsList::slotSave()
{
    QFile file(fileName);

    if (file.open(QIODevice::WriteOnly)) {

        QTextStream stream(&file);
        stream.setCodec("UTF-8");
        stream<< ui->plainTextEdit->toPlainText();
        file.close();
        emit changeWindowTitle(fileName);

        QMessageBox::about(this, "Status", "Файл успешно сохранен");
    } else {
        QMessageBox::about(this, "Status", "Ошибка при сохранении файла");
    }


}


void ProductsList::slotLoad()
{
        if (fileName.isEmpty()) {
            return;
        } else {
            QFile file(fileName);
            if (file.open(QIODevice::ReadOnly)) {
                QTextStream stream(&file);
                ui->plainTextEdit->setPlainText(stream.readAll());
                file.close();
                emit changeWindowTitle(fileName);
            }
        }
}

