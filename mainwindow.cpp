#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* Первым делом необходимо создать объект, который будет использоваться для работы с данными нашей БД
     * и инициализировать подключение к базе данных
     * */
    db = new DataBase();
    db->connectToDataBase();

    /* После чего производим наполнение таблицы базы данных
     * контентом, который будет отображаться в TableView
     * */
    for(int i = 0; i < 1; i++){
        QVariantList data;

        data.append(QDate::currentDate()); // Получаем текущую дату для вставки в БД
        data.append("ssilka");
        data.append("Pelmeni");
        data.append(1);
        data.append(1);
        data.append("Замороженные пельмени");
        data.append("Пельмени, вода, соль");
        data.append("основное блюдо");
        data.append("Россия");
        data.append(15);
        data.append(1);
        db->inserIntoTable(data);
    }

    /* Инициализируем модель для представления данных
     * с заданием названий колонок
     * */
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

MainWindow::~MainWindow()
{
    delete ui;
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

    model->select(); // Делаем выборку данных из таблицы
}
