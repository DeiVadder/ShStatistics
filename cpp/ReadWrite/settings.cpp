#include "settings.h"

#include <QDebug>

const QString SettingsPage = QStringLiteral("SettingsPage");

const QString CurrentUser = QStringLiteral("CurrentUser");

const QString DistanceList = QStringLiteral("DistanceList");
const QString CurrentDistance = QStringLiteral("CurrentDistance");
const QString Distance = QStringLiteral("Distance");

const QString WeaponList = QStringLiteral("WeaponList");
const QString CurrentWeapon = QStringLiteral("CurrentWeapon");
const QString Weapon = QStringLiteral("Weapon");

const QString DisciplineList = QStringLiteral("DisciplineList");
const QString CurrentDiscipline = QStringLiteral("CurrentDiscipline");
const QString Discipline = QStringLiteral("Discipline");

Settings::Settings(QObject *parent) : QSettings(parent)
{

    beginGroup(SettingsPage);

    //Read CurrentUser
    m_currentUser = value(CurrentUser).toString();

    //Read DistanceList
    QStringList list;
    int size = beginReadArray(DistanceList);
    for(int i(0); i < size; i++){
        setArrayIndex(i);
        list << value(Distance).toString();
    }
    m_distanceList = list;
    endArray();
    //End Read DistanceList

    //Read CurrentDistance
    m_selectedDistance = value(CurrentDistance).toString();
    //End CurrentDistance

    //Read WeaponList
    list.clear();
    size = beginReadArray(WeaponList);
    for(int i(0); i < size; i++) {
        setArrayIndex(i);
        list << value(Weapon).toString();
    }
    m_weaponList = list;
    endArray();
    //End Read WeaponList

    //Read current weapon
    m_selectedWeapon = value(CurrentWeapon).toString();
    //End read current weapon

    //Read DisciplineList
    list.clear();
    size = beginReadArray(DisciplineList);
    for(int i(0); i < size; i++) {
        setArrayIndex(i);
        list << value(Discipline).toString();
    }
    m_disciplineList = list;
    endArray();
    //End Read DisciplineList

    //Read CurrentDiscipline
    m_selectedDiscipline = value(CurrentDiscipline).toString();
    //End read CurrentDiscipline

    endGroup();
}

void Settings::setCurrentUser(const QString &currentUser)
{
    if (m_currentUser == currentUser)
        return;

    m_currentUser = currentUser;
    emit currentUserChanged(m_currentUser);

    beginGroup(SettingsPage);
    setValue(CurrentUser, currentUser);
    endGroup();
}

void Settings::setWeaponList(QStringList weaponList)
{
    sort(weaponList);
    if (m_weaponList == weaponList)
        return;

    m_weaponList = weaponList;
    emit weaponListChanged(m_weaponList);
    beginGroup(SettingsPage);
    beginWriteArray(WeaponList);
    for(int i(0); i < m_weaponList.size(); i++) {
        setArrayIndex(i);
        setValue(Weapon, m_weaponList.at(i));
    }
    endArray();
    endGroup();
}

void Settings::setSelectedWeapon(const QString &selectedWeapon)
{
    if (m_selectedWeapon == selectedWeapon)
        return;

    m_selectedWeapon = selectedWeapon;
    emit selectedWeaponChanged(m_selectedWeapon);
    beginGroup(SettingsPage);
    setValue(CurrentWeapon, m_selectedWeapon);
    endGroup();
}

void Settings::setDistanceList(QStringList distanceList)
{
    qDebug() << Q_FUNC_INFO << distanceList;
    sort(distanceList);
    if (m_distanceList == distanceList)
        return;

    m_distanceList = distanceList;
    emit distanceListChanged(m_distanceList);

    beginGroup(SettingsPage);
    beginWriteArray(DistanceList);
    for(int i(0), j(m_distanceList.size()); i < j; i++) {
        setArrayIndex(i);
        setValue(Distance, m_distanceList.at(i));
    }
    endArray();
    endGroup();
}

void Settings::setSelectedDistance(const QString &selectedDistance)
{
    if (m_selectedDistance == selectedDistance)
        return;

    m_selectedDistance = selectedDistance;
    emit selectedDistanceChanged(m_selectedDistance);
    beginGroup(SettingsPage);
    setValue(CurrentDistance, m_selectedDistance);
    endGroup();
}

void Settings::setDisciplineList(QStringList disciplineList)
{
    sort(disciplineList);
    if (m_disciplineList == disciplineList)
        return;

    m_disciplineList = disciplineList;
    emit disciplineListChanged(m_disciplineList);

    beginGroup(SettingsPage);
    beginWriteArray(DisciplineList);
    for(int i(0), j(m_disciplineList.size()); i < j; i++) {
        setArrayIndex(i);
        setValue(Discipline, m_disciplineList.at(i));
    }
    endArray();
}

void Settings::setSelectedDiscipline(const QString &selectedDiscipline)
{
    if (m_selectedDiscipline == selectedDiscipline)
        return;

    m_selectedDiscipline = selectedDiscipline;
    emit selectedDisciplineChanged(m_selectedDiscipline);

    beginGroup(SettingsPage);
    setValue(CurrentDiscipline, m_selectedDiscipline);
    endGroup();
}

void Settings::sort(QStringList &listToSort)
{
    std::sort(listToSort.begin(), listToSort.end(), [](const QString &one, const QString &other)->bool {
//        if(one.isEmpty() || other.isEmpty())
//            return false;

//        if(one.at(0).isUpper() && other.at(0).isLower())
//           return false;
//        if(one.at(0).isLower() && other.at(0).isUpper())
//           return true;
        return  one < other;
    });
}
