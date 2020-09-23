#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>

class Settings : public QSettings
{
    Q_OBJECT
    Q_PROPERTY(QString currentUser READ currentUser WRITE setCurrentUser NOTIFY currentUserChanged)

    Q_PROPERTY(QStringList weaponList READ weaponList WRITE setWeaponList NOTIFY weaponListChanged)
    Q_PROPERTY(QString selectedWeapon READ selectedWeapon WRITE setSelectedWeapon NOTIFY selectedWeaponChanged)

    Q_PROPERTY(QStringList distanceList READ distanceList WRITE setDistanceList NOTIFY distanceListChanged)
    Q_PROPERTY(QString selectedDistance READ selectedDistance WRITE setSelectedDistance NOTIFY selectedDistanceChanged)

    Q_PROPERTY(QStringList disciplineList READ disciplineList WRITE setDisciplineList NOTIFY disciplineListChanged)
    Q_PROPERTY(QString selectedDiscipline READ selectedDiscipline WRITE setSelectedDiscipline NOTIFY selectedDisciplineChanged)

private:
    QString m_currentUser;

    QStringList m_weaponList;
    QString m_selectedWeapon;

    QStringList m_distanceList;
    QString m_selectedDistance;

    QStringList m_disciplineList;
    QString m_selectedDiscipline;

public:
    explicit Settings(QObject *parent = nullptr);

    [[nodiscard]] const inline QString &currentUser() const noexcept { return m_currentUser; }

    [[nodiscard]] const inline QStringList &weaponList() const noexcept { return m_weaponList; }
    [[nodiscard]] const inline QString &selectedWeapon() const noexcept { return m_selectedWeapon; }

    [[nodiscard]] const inline QStringList &distanceList() const noexcept { return m_distanceList;}
    [[nodiscard]] const inline QString &selectedDistance() const noexcept { return m_selectedDistance; }

    [[nodiscard]] const inline QStringList &disciplineList() const noexcept { return m_disciplineList; }
    [[nodiscard]] const inline QString selectedDiscipline() const noexcept { return m_selectedDiscipline; }


public slots:
    void setCurrentUser(const QString &currentUser);

    void setWeaponList(QStringList weaponList);
    void setSelectedWeapon(const QString &selectedWeapon);

    void setDistanceList(QStringList distanceList);
    void setSelectedDistance(const QString &selectedDistance);

    void setDisciplineList(QStringList disciplineList);
    void setSelectedDiscipline(const QString &selectedDiscipline);


signals:
    void currentUserChanged(const QString &currentUser);
    void weaponListChanged(const QStringList &weaponList);
    void selectedWeaponChanged(const QString &selectedWeapon);
    void distanceListChanged(const QStringList &distanceList);
    void selectedDistanceChanged(const QString &selectedDistance);
    void disciplineListChanged(const QStringList &disciplineList);
    void selectedDisciplineChanged(const QString &selectedDiscipline);


private:
    void sort(QStringList &listToSort);
};

#endif // SETTINGS_H
