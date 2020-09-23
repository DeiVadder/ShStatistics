#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QObject>


class QSqlQuery;
class Database : public QObject
{
public:
    explicit Database(QObject *parent = nullptr);

public slots:
    void addNewEntry(double pointX,
                     double pointY,
                     double points,
                     int distance,
                     const QString &weapon,
                     const QString &uuid,
                     const QString &discipline,
                     const QString &table = QStringLiteral("User1"));

    QStringList listOfAvailableTables();
    void addNewTable(const QString &name);

private:
    void init();

private:
    QSqlDatabase m_db;
    QSqlQuery *m_query = nullptr;
};

#endif // DATABASE_H
