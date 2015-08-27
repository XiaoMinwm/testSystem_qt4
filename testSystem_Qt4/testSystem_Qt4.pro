#-------------------------------------------------
#
# Project created by QtCreator 2011-11-03T10:16:31
#
#-------------------------------------------------

QT       += core gui
QT       +=sql

TARGET = testSystem_Qt4
TEMPLATE = app


SOURCES += main.cpp\
        login.cpp \
    adminform.cpp \
    addthform.cpp \
    addstdform.cpp \
    teacherform.cpp \
    studentform.cpp

HEADERS  += login.h \
    adminform.h \
    addthform.h \
    addstdform.h \
    teacherform.h \
    studentform.h \
    database.h

FORMS    += login.ui \
    adminform.ui \
    addthform.ui \
    addstdform.ui \
    teacherform.ui \
    studentform.ui
