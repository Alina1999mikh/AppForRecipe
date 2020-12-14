#include "viewrecipe.h"
#include "ui_viewrecipe.h"

viewRecipe::viewRecipe(const QModelIndex& index, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::viewRecipe)
{
    ui->setupUi(this);
}

viewRecipe::~viewRecipe()
{
    delete ui;
}

void viewRecipe::on_pushButton_clicked()
{
    close();
}
