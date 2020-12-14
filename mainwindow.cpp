#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextEdit>
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

    sqlDb= QSqlDatabase::addDatabase("QSQLITE");
    sqlDb.setDatabaseName("C:\\example\\"+db->getDataBaseName());
\
   // loadDataBase();
    myInsertRecipe=new InsertRecipe();
    connect(ui->pushButton, SIGNAL(clicked()), myInsertRecipe, SLOT(show()));
    //connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(reload()));
//    connect(ui->tableView, SIGNAL(clicked(const QModelIndex &)), viewrecipe, SLOT(show()));
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

//    QModelIndex index = ui->tableView->model()->index(1,1);
//    QLabel *lblImage = new QLabel();
//    lblImage->setPixmap(QPixmap("C:\\Users\\flenn\\OneDrive\\Desktop\\viz_rest\\base\\ovsyanka.jpg"));
//    ui->tableView->setIndexWidget(index, lblImage);
}

void MainWindow::createUI()
{

     model->select(); // Делаем выборку данных из таблицы
     ui->tableView->setModel(model);     // Устанавливаем модель на TableView
     ui->tableView->setColumnHidden(0, true);    // Скрываем колонку с id записей
       // Разрешаем выделение строк
     ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
       // Устанавливаем режим выделения лишь одно строки в таблице
     ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
       // Устанавливаем размер колонок по содержимому
     ui->tableView->resizeColumnsToContents();
     ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
     ui->tableView->horizontalHeader()->setStretchLastSection(true);


}


void MainWindow::handleOnTableClicked(const QModelIndex &index) {
  if (index.isValid()) {
    QString cellText = index.data().toString();
    //TODO:
    qDebug() << cellText << "kkkkkkkkkkkkk\n";
   }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    model->select(); // Делаем выборку данных из таблицы
}
void MainWindow::reload()
{
    createUI();
}

void MainWindow::on_pushButton_2_clicked()
{
    //ui->tableView->;
    createUI();
}

void MainWindow::on_pushButton_3_clicked() {
    QItemSelectionModel *select = ui->tableView->selectionModel();

    if (select->hasSelection()) {
        QVariantList data;
        QModelIndexList lst = select->selectedRows();

        int rowNum = lst.at(0).row();
        for (int i = 0; i < model->columnCount(); i ++) {
            data.append(ui->tableView->model()->data(ui->tableView->model()->index(rowNum,i),0));
            //qDebug() << data.at(i).toString();
        }
        db->deleteFromTableIn(data.at(0).toString());

        model->select();
    }
}
