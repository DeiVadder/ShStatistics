#include "database.h"
#include "cpp/ReadWrite/preapptasks.h"


#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>

#include <QDebug>

Database::Database(QObject *parent) : QObject(parent)
{
    m_db = PreAppTasks::getDefaultDatabase();
    init();
}

void Database::addNewEntry(double pointX, double pointY,
                           double points,
                           int distance,
                           const QString &weapon,
                           const QString &uuid,
                           const QString &discipline,
                           const QString &table)
{
    if(m_query) {
        m_query->prepare("INSERT INTO " + table + " (timestamp, pointX, pointY, points, dist, weapon, partOfSet) "
                                                  "VALUES (:timestamp, :pointX, :pointY, :points, :dist, :weapon, :discipline, :partOfSet);");
        m_query->bindValue(QStringLiteral(":timestamp"), QDateTime::currentDateTime());
        m_query->bindValue(QStringLiteral(":pointX"), pointX);
        m_query->bindValue(QStringLiteral(":pointY"), pointY);
        m_query->bindValue(QStringLiteral(":points"), points);
        m_query->bindValue(QStringLiteral(":dist"),distance);
        m_query->bindValue(QStringLiteral(":weapon"), weapon);
        m_query->bindValue(QStringLiteral(":discipline"), discipline);
        m_query->bindValue(QStringLiteral(":partOfSet"), uuid);

        if(!m_query->exec())
            qDebug() << "Could not insert new entry" << m_query->lastError();
    }
}

QStringList Database::listOfAvailableTables()
{
    QStringList list;
    if(m_query){
        if(m_query->exec("SELECT name FROM sqlite_master WHERE type='table' ORDER BY name;")) {
            while(m_query->next()){
                list << m_query->value(0).toString();
            }
        } else {
            qDebug() << m_query->lastError();
        }
    }
    return list;
}

void Database::addNewTable(const QString &name)
{
    if(m_query) {
        //Contents of:
        /* Unique Identifier,                   //[0]
         * DateTime-stamp,                      //[1]
         * PointX (double normed 0 - 1),        //[2]
         * PointY (double normed 0 - 1),        //[3]
         * Points (int 0 - 10 , double 10 - 11) //[4]
         * Distance(int meters)                 //[5]
         * Weapon (TEXT)                        //[6]
         * Discipline(TEXT)                     //[7]
         * Set (TEXT UUID)                      //[8]
         */
        m_query->prepare(QStringLiteral("CREATE TABLE IF NOT EXISTS '")+ name + QStringLiteral("' ("
                                        "id INTEGER PRIMARY KEY, "
                                        "timestamp DATETIME NOT NULL,"
                                        "pointX DOUBLE,"
                                        "pointY DOUBLE,"
                                        "points DOUBLE,"
                                        "dist   INT,"
                                        "weapon TEXT,"
                                        "discipline TEXT,"
                                        "partOfSet TEXT);"));
        if(!m_query->exec())
            qDebug() << "ERROR CREATING NEW TABLE" << m_query->lastError();
    }
}

void Database::init()
{
    if(!m_db.isOpen()) {
        m_db.setDatabaseName(PreAppTasks::DatabasePath());
        m_db.open();
    }

    //Create default table when not there
    m_query = new QSqlQuery(m_db);

    //Aliases (Table to User) together with general settings are part of the Settings class
    //Create 1 Table (Default User1)
//    addNewTable(QStringLiteral("User1"));
}
