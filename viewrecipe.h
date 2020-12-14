#ifndef VIEWRECIPE_H
#define VIEWRECIPE_H

#include <QWidget>

namespace Ui {
class viewRecipe;
}

class viewRecipe : public QWidget
{
    Q_OBJECT

public:
    explicit viewRecipe(const QModelIndex& index, QWidget *parent = 0);
    ~viewRecipe();

private slots:
    void on_pushButton_clicked();

private:
    Ui::viewRecipe *ui;
};

#endif // VIEWRECIPE_H
