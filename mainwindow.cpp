#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextEdit>
#include "insertrecipe.h"

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
       ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setColumnHidden(0, true);    // Скрываем колонку с id записей
    // Разрешаем выделение строк
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Устанавливаем режим выделения лишь одно строки в таблице
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

}

void MainWindow::on_pushButton_2_clicked()
{
    //ui->tableView->;
    createUI();
}
