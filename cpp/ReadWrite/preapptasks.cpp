#include "preapptasks.h"

#include <QCoreApplication>
#include <QStandardPaths>
#include <QDir>

#include <QSqlDatabase>

void PreAppTasks::setAppVariables()
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setApplicationName(QStringLiteral("CompetitionAnalytics"));
    QCoreApplication::setOrganizationName(QStringLiteral("JonasWorkshop"));
}

const QString PreAppTasks::DataFolder()
{
    return QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
}

const QString PreAppTasks::DatabasePath()
{
    return DataFolder() + QStringLiteral("/ShootingDatabase.db");
}

void PreAppTasks::addDefaultDataBasePath()
{
    QSqlDatabase::addDatabase(QStringLiteral("QSQLITE"), QStringLiteral("DefaultConection"));
}

QSqlDatabase &PreAppTasks::getDefaultDatabase()
{
    static QSqlDatabase db = QSqlDatabase::database(QStringLiteral("DefaultConection"),false);
    return db;
}

void PreAppTasks::createAppFolder()
{
    //On some OS's, the AppDataLocation must be created first (iOS), We check for existence, and if it does not exist we create the path
    QDir dir;
    if (!dir.exists(DataFolder())){
        dir.mkpath(DataFolder());
    }
}
