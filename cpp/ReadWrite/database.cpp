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
                           const QString &table)
{
    if(m_query) {
        m_query->prepare("INSERT INTO " + table + " (timestamp, pointX, pointY, points, dist, weapon, partOfSet) "
                                                  "VALUES (:timestamp, :pointX, :pointY, :points, :dist, :weapon, :partOfSet);");
        m_query->bindValue(QStringLiteral(":timestamp"), QDateTime::currentDateTime());
        m_query->bindValue(QStringLiteral(":pointX"), pointX);
        m_query->bindValue(QStringLiteral(":pointY"), pointY);
        m_query->bindValue(QStringLiteral(":points"), points);
        m_query->bindValue(QStringLiteral(":dist"),distance);
        m_query->bindValue(QStringLiteral(":weapon"), weapon);
        m_query->bindValue(QStringLiteral(":partOfSet"), uuid);

        if(!m_query->exec())
            qDebug() << "Could not insert new entry" << m_query->lastError();
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
    //Contents of:
    /* Unique Identifier,                   //[0]
     * DateTime-stamp,                      //[1]
     * PointX (double normed 0 - 1),        //[2]
     * PointY (double normed 0 - 1),        //[3]
     * Points (int 0 - 10 , double 10 - 11) //[4]
     * Distance(int meters)                 //[5]
     * Weapon (TEXT)                        //[6]
     * Set (TEXT UUID)                      //[7]
     */
    m_query->prepare(QStringLiteral("CREATE TABLE IF NOT EXISTS User1 ("
                                    "id INTEGER PRIMARY KEY, "
                                    "timestamp DATETIME NOT NULL,"
                                    "pointX DOUBLE,"
                                    "pointY DOUBLE,"
                                    "points DOUBLE,"
                                    "dist   INT,"
                                    "weapon TEXT,"
                                    "partOfSet TEXT);"));
    if(!m_query->exec())
        qDebug() << "ERROR CREATING DEFAULT TABLE" << m_query->lastError();
}
