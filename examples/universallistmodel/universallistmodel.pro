QT += quick qml
TEMPLATE=app

INCLUDEPATH +=../../qt
HEADERS += \
    ../../qt/universallistmodel.h \
    sampleobject.h

SOURCES += \
    ../../qt/universallistmodel.cpp \
    sampleobject.cpp \
    main.cpp

RESOURCES += \
    resources.qrc

DISTFILES += \
    main.qml
