#include "backendproperties.h"

BackendProperties::BackendProperties(QObject *parent) : QObject(parent)
{
    reset();
}

void BackendProperties::reset()
{
    setModelCurrentUser(QStringList());
}

void BackendProperties::setModelCurrentUser(const QStringList &modelCurrentUser)
{
    if (m_modelCurrentUser == modelCurrentUser)
        return;

    m_modelCurrentUser = modelCurrentUser;
    emit modelCurrentUserChanged(m_modelCurrentUser);
}
