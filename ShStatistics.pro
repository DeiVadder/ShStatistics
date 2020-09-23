QT += quick sql

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000
DEFINES += QMLSOURCEDIR=\\\"$$PWD\\\"

SOURCES += \
        cpp/ReadWrite/database.cpp \
        cpp/ReadWrite/preapptasks.cpp \
        cpp/ReadWrite/settings.cpp \
        cpp/backend.cpp \
        cpp/backendproperties.cpp \
        cpp/main.cpp

RESOURCES += qml.qrc \
    rsc.qrc

TRANSLATIONS += \
    ShStatistics_de_DE.ts

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    cpp/ReadWrite/database.h \
    cpp/ReadWrite/preapptasks.h \
    cpp/ReadWrite/settings.h \
    cpp/backend.h \
    cpp/backendproperties.h
