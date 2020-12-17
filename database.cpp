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

bool DataBase::deleteFromTableIn(const QString& id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM " TABLE " WHERE ID=" + id);

    if(!query.exec()){
        qDebug() << "error delete from " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}

/* Методы восстановления базы данных
 * */
bool DataBase::restoreDataBase()
{
    if(this->openDataBase()){
        if(!this->createTable()){
            qDebug() << "error create";
            return false;
        } else {
            qDebug() << "success create";
            return true;
        }
    } else {
        qDebug() << "error restore";
        return false;
    }
    qDebug() << "success restore";

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
         qDebug()<<"success open";
         return true;
     } else {
         qDebug()<<"error open";
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
                 TABLE_COUNTRY            " VARCHAR(30),"
                 TABLE_TIME               " INTEGER, "
                 TABLE_COMPLEXITY         " VARCHAR(15)   NOT NULL"
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
    query.bindValue(":Like",     data[3]);
    query.bindValue(":Was",     data[4]);
    query.bindValue(":Recipe",        data[5].toString());
    query.bindValue(":Ingredients",        data[6].toString());
    query.bindValue(":Kind",      data[7].toString());
    query.bindValue(":Country",     data[8].toString());
    query.bindValue(":Time",        data[9].toInt());
    query.bindValue(":Complexity",        data[10].toString());

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

QString DataBase::getDataBaseName(){
    return DATABASE_NAME;
}
