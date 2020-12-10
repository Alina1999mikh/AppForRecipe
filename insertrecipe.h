#ifndef INSERTRECIPE_H
#define INSERTRECIPE_H

#include <QWidget>

namespace Ui {
class InsertRecipe;
}

class InsertRecipe : public QWidget
{
    Q_OBJECT

public:
    explicit InsertRecipe(QWidget *parent = 0);
    ~InsertRecipe();

private slots:
    void on_pushButton_clicked();

private:

    Ui::InsertRecipe *ui;
};

#endif // INSERTRECIPE_H
