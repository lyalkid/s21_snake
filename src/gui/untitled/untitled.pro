QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../brick_game/brick_game.c \
    ../../brick_game/snake/controller/controller.cpp \
    ../../brick_game/snake/model/Snake.cpp \
    ../../brick_game/tetris/src/TGM3Randomizer.c \
    ../../brick_game/tetris/src/field_mechanics.c \
    ../../brick_game/tetris/src/game_api.c \
    ../../brick_game/tetris/src/game_rules.c \
    ../../brick_game/tetris/src/game_state_management.c \
    ../../brick_game/tetris/src/tetramino.c \
    ../../brick_game/tetris/src/tetramino_movement.c \
    ../../brick_game/utils/timer.c \
    ../../brick_game/utils/utilities.c \
    main.cpp \
    mainwindow.cpp \
    snake_widget.cpp \
    tetris_widget.cpp

HEADERS += \
    ../../brick_game/brick_game.h \
    ../../brick_game/snake/controller/controller.h \
    ../../brick_game/snake/model/Snake.h \
    ../../brick_game/tetris/inc/tetramino_movement.h \
    ../../brick_game/tetris/inc/tetris.h \
    ../../brick_game/utils/timer.h \
    ../../brick_game/utils/defines.h \
    ../../brick_game/utils/utilities.h \
    mainwindow.h \
    snake_widget.h \
    tetris_widget.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
