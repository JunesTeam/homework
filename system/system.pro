QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addmaterial.cpp \
    addstudent.cpp \
    admin.cpp \
    globle.cpp \
    leave_stu.cpp \
    leavesystem.cpp \
    listmaterial.cpp \
    liststudent.cpp \
    listuser.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    pass1.cpp \
    pass2.cpp \
    studentform.cpp \
    system.cpp

HEADERS += \
    addmaterial.h \
    addstudent.h \
    admin.h \
    globle.h \
    leave_stu.h \
    leavesystem.h \
    listmaterial.h \
    liststudent.h \
    listuser.h \
    login.h \
    mainwindow.h \
    pass1.h \
    pass2.h \
    studentform.h \
    system.h

FORMS += \
    addmaterial.ui \
    addstudent.ui \
    admin.ui \
    leave_stu.ui \
    leavesystem.ui \
    listmaterial.ui \
    liststudent.ui \
    listuser.ui \
    login.ui \
    mainwindow.ui \
    pass1.ui \
    pass2.ui \
    studentform.ui \
    system.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

QT += sql
