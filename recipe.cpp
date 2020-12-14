#include "Recipe.h"
#include "ui_Recipe.h"

Recipe::Recipe(QWidget *parent) :
    QWidget(parent),
    i(new Ui::Recipe)
{
    ui->setupUi(this);
}

Recipe::~Recipe()
{
    delete ui;
}
