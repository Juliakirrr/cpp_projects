QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

DESTDIR = $$PWD/../../../build

TARGET = brick_game

# Отключение предупреждений о неиспользуемых результатах
QMAKE_CXXFLAGS += -Wno-unused-result

# Отключение предупреждений о неинициализированных переменных
QMAKE_CXXFLAGS += -Wno-maybe-uninitialized

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    snakeD.cpp \
    tetris.cpp \
    ../../../brick_game/tetris/back.cpp \
    ../../cli/tetris/front.cpp \
    ../../../brick_game/snake/snake.cpp

HEADERS += \
    mainwindow.h \
    snakeD.h \
    tetris.h \
    ../../cli/tetris/main.h \
    ../../../brick_game/snake/snake.h

FORMS += \
    mainwindow.ui \
    snakeD.ui \
    tetris.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    higt_score

LIBS += -lncurses
