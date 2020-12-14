#ifndef Recipe_H
#define Recipe_H

#include <QWidget>

namespace Ui {
class Recipe;
}

class Recipe : public QWidget
    {
    Q_OBJECT

public:
    explicit Recipe(QWidget *parent = 0);
    ~Recipe();

private:
    Ui::Recipe *ui;
};

#endif // Recipe_H
