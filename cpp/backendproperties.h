#ifndef BACKENDPROPERTIES_H
#define BACKENDPROPERTIES_H

#include <QObject>

class BackendProperties : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QStringList modelCurrentUser READ modelCurrentUser WRITE setModelCurrentUser NOTIFY modelCurrentUserChanged)
public:
    explicit BackendProperties(QObject *parent = nullptr);

    void reset();

    [[nodiscard]] const inline QStringList &modelCurrentUser() const noexcept { return m_modelCurrentUser; }

public slots:
    void setModelCurrentUser(const QStringList &modelCurrentUser);

signals:
    void modelCurrentUserChanged(const QStringList &modelCurrentUser);

private:
    QStringList m_modelCurrentUser;
};

#endif // BACKENDPROPERTIES_H
