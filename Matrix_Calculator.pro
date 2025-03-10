QT += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = matrix_calculator
TEMPLATE = app

SOURCES += main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS +=

RESOURCES += \
    resources.qrc

DISTFILES +=
