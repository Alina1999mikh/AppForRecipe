#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "database.h"
#include "insertrecipe.h"
#include "viewrecipe.h"
#include <QSqlTableModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    DataBase        *db;
    ~MainWindow();
    void loadDataBase();


private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

public slots:
    //
void handleOnTableClicked(const QModelIndex &index) ;

private:
    Ui::MainWindow  *ui;
    InsertRecipe *myInsertRecipe;
    QSqlTableModel  *model;
    void addHandRecipe();
    QSqlDatabase sqlDb;
    void setupModel(const QString &tableName, const QStringList &headers);
      void createUI();
};

#endif // MAINWINDOW_H
