#include "insertrecipe.h"
#include "ui_insertrecipe.h"

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
