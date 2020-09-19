#ifndef PREAPPTASKS_H
#define PREAPPTASKS_H

#include <QString>

class QSqlDatabase;
class PreAppTasks
{
public:
    PreAppTasks() = default;

    static void setAppVariables();
    static const QString DataFolder();
    static const QString DatabasePath();
    static void addDefaultDataBasePath();
    static QSqlDatabase &getDefaultDatabase();

    static void createAppFolder();
};

#endif // PREAPPTASKS_H
