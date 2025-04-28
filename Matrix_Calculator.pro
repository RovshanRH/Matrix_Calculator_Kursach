QT += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = matrix_calculator
TEMPLATE = app

SOURCES += main.cpp \
    cleaner.cpp \
    copymatrix.cpp \
    insertmatrix.cpp \
    inverse.cpp \
    matrix.cpp \
    matrix_calculator.cpp \
    operations.cpp \
    randomizer.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    cleaner.h \
    copymatrix.h \
    insertmatrix.h \
    inverse.h \
    matrix.h \
    matrix_calculator.h \
    operations.h \
    randomizer.h

RESOURCES += \
    resources.qrc

RC_ICONS = myappico.ico

DISTFILES +=

# LIBS += -lgtest -lgtest_main
