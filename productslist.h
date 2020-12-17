#ifndef PRODUCTSLIST_H
#define PRODUCTSLIST_H

#include <QWidget>

namespace Ui {
class ProductsList;
}

class ProductsList : public QWidget
{
    Q_OBJECT

public:
    explicit ProductsList(QWidget *parent = 0);
    ~ProductsList();

signals:
    void changeWindowTitle(const QString&);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void slotSave();

    void slotLoad();

private:
    Ui::ProductsList *ui;
    QString fileName;
};

#endif // PRODUCTSLIST_H
