#ifndef VIEWRECIPE_H
#define VIEWRECIPE_H

#include <QWidget>
#include <QSqlQuery>

namespace Ui {
class viewRecipe;
}

class viewRecipe : public QWidget
{
    Q_OBJECT

public:
    explicit viewRecipe(QString id, QWidget *parent = 0);
    ~viewRecipe();

private slots:
    void on_pushButton_clicked();

private:
    Ui::viewRecipe *ui;
    QString id;
    void loadData();
    void setForm();
};

#endif // VIEWRECIPE_H
