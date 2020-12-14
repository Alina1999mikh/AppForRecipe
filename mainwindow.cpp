#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "insertrecipe.h"
#include "viewrecipe.h"

#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = new DataBase();
    db->connectToDataBase();
    this->setupModel(TABLE,
                         QStringList() << trUtf8("id")
                                       << trUtf8("Дата")
                                       << trUtf8("Фото")
                                       << trUtf8("Имя")
                                       << trUtf8("Лайк")
                                       << trUtf8("Было")
                                       << trUtf8("Рецепт")
                                       << trUtf8("Ингредиенты")
                                       << trUtf8("Тип")
                                       << trUtf8("страна")
                                         << trUtf8("Время")
                                         << trUtf8("Сложность")
                   );

        /* Инициализируем внешний вид таблицы с данными
         * */
        this->createUI();
}

/* Метод для инициализации модеи представления данных
 * */
void MainWindow::setupModel(const QString &tableName, const QStringList &headers)
{
    /* Производим инициализацию модели представления данных
     * с установкой имени таблицы в базе данных, по которому
     * будет производится обращение в таблице
     * */
    model = new QSqlTableModel(this);
    model->setTable(tableName);

    /* Устанавливаем названия колонок в таблице с сортировкой данных
     * */
    for(int i = 0, j = 0; i < model->columnCount(); i++, j++){
        model->setHeaderData(i,Qt::Horizontal,headers[j]);
    }
    // Устанавливаем сортировку по возрастанию данных по нулевой колонке
    model->setSort(0,Qt::AscendingOrder);
}

void MainWindow::createUI()
{
     ui->tableView->setColumnHidden(0, true);    // Скрываем колонку с id записей
       // Разрешаем выделение строк
     ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
       // Устанавливаем режим выделения лишь одно строки в таблице
     ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
       // Устанавливаем размер колонок по содержимому
     ui->tableView->resizeColumnsToContents();
     ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
     ui->tableView->horizontalHeader()->setStretchLastSection(true);
     model->select(); // Делаем выборку данных из таблицы
     ui->tableView->setModel(model);     // Устанавливаем модель на TableView
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    InsertRecipe *myInsertRecipe=new InsertRecipe();
    myInsertRecipe->show();
}

void MainWindow::on_pushButton_2_clicked()
{
     model->select();
}

void MainWindow::on_pushButton_3_clicked() {
    QItemSelectionModel *select = ui->tableView->selectionModel();

    if (select->hasSelection()) {
        QVariantList data;
        QModelIndexList lst = select->selectedRows();

        int rowNum = lst.at(0).row();
        for (int i = 0; i < model->columnCount(); i ++) {
            data.append(ui->tableView->model()->data(ui->tableView->model()->index(rowNum,i),0));
        }
        db->deleteFromTableIn(data.at(0).toString());

        model->select();
    }
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    viewRecipe *myViewRecipe=new viewRecipe(index) ;
    myViewRecipe->show();
}
