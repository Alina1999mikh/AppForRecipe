#include "database.h"
#include <string.h>

#include <QString>
DataBase::DataBase(QObject *parent) : QObject(parent)
{

}

DataBase::~DataBase()
{

}

/* Методы для подключения к базе данных
 * */
void DataBase::connectToDataBase()
{
    /* Перед подключением к базе данных производим проверку на её существование.
     * В зависимости от результата производим открытие базы данных или её восстановление
     * */
    if(!QFile("C:/example/" DATABASE_NAME).exists()){
        this->restoreDataBase();
    } else {
        this->openDataBase();
    }
}

/* Методы восстановления базы данных
 * */
bool DataBase::restoreDataBase()
{
    if(this->openDataBase()){
        if(!this->createTable()){
            return false;
        } else {
            return true;
        }
    } else {
        qDebug() << "Не удалось восстановить базу данных";
        return false;
    }
    return false;
}

/* Метод для открытия базы данных
 * */
bool DataBase::openDataBase()
{
    /* База данных открывается по заданному пути
     * и имени базы данных, если она существует
     * */
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(DATABASE_HOSTNAME);
    db.setDatabaseName("C:/example/" DATABASE_NAME);
    if(db.open()){
        return true;
    } else {
        return false;
    }
}

/* Методы закрытия базы данных
 * */
void DataBase::closeDataBase()
{
    db.close();
}

/* Метод для создания таблицы в базе данных
 * */
bool DataBase::createTable()
{
    /* В данном случае используется формирование сырого SQL-запроса
     * с последующим его выполнением.
     * */
    QSqlQuery query;
    if(!query.exec( "CREATE TABLE " TABLE " ("
                            "id INTEGER PRIMARY KEY AUTOINCREMENT, "

                 TABLE_DATE               " DATE   NOT NULL,"
                 TABLE_PHOTO              " VARCHAR(100)   NOT NULL,"
                 TABLE_NAME               " VARCHAR(15)   NOT NULL,"
                 TABLE_LIKE               " BOOLEAN   NOT NULL,"
                 TABLE_WAS                " BOOLEAN   NOT NULL,"
                 TABLE_RECIPE             " VARCHAR(255)   NOT NULL,"
                 TABLE_INGREDIENTS        " VARCHAR(255)   NOT NULL,"
                 TABLE_KIND               " VARCHAR(15)   NOT NULL,"
                 TABLE_COUNTRY            " VARCHAR(30)   NOT NULL,"
                 TABLE_TIME               " INTEGER   NOT NULL,"
                 TABLE_COMPLEXITY         " INTEGER   NOT NULL"
                        " )"
                    )){
        qDebug() << "DataBase: error of create " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}

/* Метод для вставки записи в базу данных
 * */
bool DataBase::inserIntoTable(const QVariantList &data)
{
    /* Запрос SQL формируется из QVariantList,
     * в который передаются данные для вставки в таблицу.
     * */
    QSqlQuery query;
    /* В начале SQL запрос формируется с ключами,
     * которые потом связываются методом bindValue
     * для подстановки данных из QVariantList
     * */
    query.prepare("INSERT INTO " TABLE " ( " TABLE_DATE ", "
                                             TABLE_PHOTO ", "
                                             TABLE_NAME ", "
                                             TABLE_LIKE ", "
                                             TABLE_WAS ", "
                                             TABLE_RECIPE ", "
                                              TABLE_INGREDIENTS ", "
                                              TABLE_KIND ", "
                                              TABLE_COUNTRY ", "
                                              TABLE_TIME ", "
                                               TABLE_COMPLEXITY " ) "
                  "VALUES (:Date, :Photo, :Name, :Like, :Was, :Recipe, :Ingredients, :Kind, :Country, :Time, :Complexity )");
    query.bindValue(":Date",        data[0].toDate());
    query.bindValue(":Photo",        data[1].toString());
    query.bindValue(":Name",        data[2].toString());

   QString str="i don't";
    if(data[3]==true) str="i like it";
    query.bindValue(":Like",     str);
    str="i don't";
    if(data[4]==true) str="i like it";
    query.bindValue(":Was",     str);
    query.bindValue(":Recipe",        data[5].toString());
    query.bindValue(":Ingredients",        data[6].toString());
    query.bindValue(":Kind",      data[7].toString());
    query.bindValue(":Country",     data[8].toString());
    query.bindValue(":Time",        data[9].toInt());
    query.bindValue(":Complexity",        data[10].toInt());

    // После чего выполняется запросом методом exec()
    if(!query.exec()){
        qDebug() << "error insert into " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}
