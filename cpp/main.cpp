#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "cpp/ReadWrite/preapptasks.h"
#include "cpp/ReadWrite/settings.h"

//#include "cpp/ReadWrite/database.h"

#include "backend.h"

#include <QDebug>
#include <QUuid>
#include <QQmlContext>

class DynamicReload : public QObject
{
    Q_OBJECT
public:
    explicit DynamicReload(QObject *parent = nullptr) : QObject(parent) {}

signals:
    void reloadQML();
};


void clearAndReload(QQmlApplicationEngine &engine){
    for(QObject *obj : engine.rootObjects()){
        engine.rootObjects().removeOne(obj);
        obj->deleteLater();
    }
    engine.clearComponentCache();
    engine.load(QUrl::fromLocalFile(QString(QMLSOURCEDIR )+ "/qml/main.qml"));
}

int main(int argc, char *argv[])
{
    PreAppTasks::setAppVariables();

    QCoreApplication::setOrganizationName(QStringLiteral("JonasWorkshop"));
    QCoreApplication::setApplicationName(QStringLiteral("CompetitionAnalytics"));
    QGuiApplication app(argc, argv);
    PreAppTasks::createAppFolder();
    PreAppTasks::addDefaultDataBasePath();

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    DynamicReload dReload;
    engine.rootContext()->setContextProperty("DynamicReload", &dReload);
    QObject::connect(&dReload, &DynamicReload::reloadQML, [&engine]()->void{clearAndReload(engine);});

    qDebug() << Q_FUNC_INFO << PreAppTasks::DatabasePath();

    Backend backend;
    engine.rootContext()->setContextProperty("Backend", &backend);

    Settings settings;
    engine.rootContext()->setContextProperty("Setting", &settings);
    /*
    Database db;
    qDebug() << db.listOfAvailableTables();
    QUuid uuid;
    QString uid = uuid.createUuid().toString();

    for(int i{0}; i < 15; i++){
        db.addNewEntry((std::rand() % 100)/100., (std::rand() % 100)/100., (std::rand() % 10), 10, "Test",uid);
    }
    */


    return app.exec();
}

#include "main.moc"
