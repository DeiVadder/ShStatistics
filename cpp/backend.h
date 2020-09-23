#ifndef BACKEND_H
#define BACKEND_H

#include "backendproperties.h"

#include "ReadWrite/database.h"

class Backend : public BackendProperties
{
    Q_OBJECT
public:
    explicit Backend(QObject *parent = nullptr);

    void init();

    Q_INVOKABLE void addNewUser(const QString &user);

signals:


private:
    Database m_DB;
};

#endif // BACKEND_H
