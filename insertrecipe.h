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

    void on_pushButton_2_clicked();

private:
    QString filename;
    Ui::InsertRecipe *ui;
    void clear();
};

#endif // INSERTRECIPE_H
