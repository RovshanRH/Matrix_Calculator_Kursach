QT += core gui widgets svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = matrix_calculator
TEMPLATE = app
TRANSLATIONS += \
    Translations/myapp_ru.ts \
    Translations/myapp_en.ts \
    Translations/myapp_de.ts \
    Translations/myapp_fr.ts \  # Французский
    Translations/myapp_es.ts \  # Испанский
    Translations/myapp_zh.ts \
    Translations/myapp_jp.ts \
    Translations/myapp_kr.ts \
    Translations/myapp_pl.ts \
    Translations/myapp_it.ts
SOURCES += main.cpp \
    cleaner.cpp \
    copymatrix.cpp \
    helpwindow.cpp \
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
    helpwindow.h \
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
