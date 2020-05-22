#-------------------------------------------------
#
# Project created by QtCreator 2019-05-24T21:37:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SmartHouse
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        menu.cpp \
    account.cpp \
    registry.cpp\
    tarif.cpp \
    mainmenu.cpp\
    counter.cpp\
    devais.cpp\
    house.cpp\
    room.cpp\
    sencor.cpp\
    temperature.cpp \
    show_tarif.cpp \
    change_tarife.cpp \
    change_pass.cpp \
    give_admin.cpp \
    add_house.cpp \
    add_room.cpp \
    info_house_o.cpp \
    del_room.cpp \
    chang_house.cpp \
    chang_room.cpp \
    work_counter.cpp \
    work_dev.cpp \
    add_devais.cpp \
    change_dev.cpp \
    info_dev.cpp \
    work_sen.cpp \
    add_cond.cpp \
    cond.cpp \
    money.cpp \
    lastuse.cpp
HEADERS += \
        menu.h \
    account.h \
    registry.h\
    tarif.h \
    mainmenu.h\
    counter.h\
    devais.h\
    house.h\
    room.h\
    sencor.h\
    temperature.h \
    show_tarif.h \
    change_tarife.h \
    change_pass.h \
    give_admin.h \
    add_house.h \
    add_room.h \
    info_house_o.h \
    del_room.h \
    chang_house.h \
    chang_room.h \
    work_counter.h \
    work_dev.h \
    add_devais.h \
    change_dev.h \
    info_dev.h \
    work_sen.h \
    add_cond.h \
    cond.h \
    money.h \
    lastuse.h

FORMS += \
        menu.ui \
    registry.ui \
    mainmenu.ui \
    show_tarif.ui \
    change_tarife.ui \
    change_pass.ui \
    give_admin.ui \
    add_house.ui \
    add_room.ui \
    info_house_o.ui \
    del_room.ui \
    chang_house.ui \
    chang_room.ui \
    work_counter.ui \
    work_dev.ui \
    add_devais.ui \
    change_dev.ui \
    info_dev.ui \
    work_sen.ui \
    add_cond.ui \
    cond.ui \
    money.ui

RESOURCES += \
    pich.qrc
