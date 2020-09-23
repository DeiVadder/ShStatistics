#include "backend.h"

Backend::Backend(QObject *parent) : BackendProperties(parent)
{
    init();
}

void Backend::init()
{
    setModelCurrentUser(m_DB.listOfAvailableTables());
}

void Backend::addNewUser(const QString &user)
{
    m_DB.addNewTable(user);
    setModelCurrentUser(m_DB.listOfAvailableTables());
}
