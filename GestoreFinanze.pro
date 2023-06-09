QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RESOURCES += \
    icons.qrc

SOURCES += \
    account.cpp \
    accountcontainer.cpp \
    addaccountdialog.cpp \
    addexpensedialog.cpp \
    addincomedialog.cpp \
    addloandialog.cpp \
    editaccountdialog.cpp \
    editexpensedialog.cpp \
    editincomedialog.cpp \
    editloandialog.cpp \
    expense.cpp \
    finance.cpp \
    income.cpp \
    jsonhandler.cpp \
    loan.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    account.h \
    accountcontainer.h \
    addaccountdialog.h \
    addexpensedialog.h \
    addincomedialog.h \
    addloandialog.h \
    editaccountdialog.h \
    editexpensedialog.h \
    editincomedialog.h \
    editloandialog.h \
    expense.h \
    finance.h \
    income.h \
    jsonhandler.h \
    loan.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
