QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DFA/dfa.cpp \
    NFA/nfa.cpp \
    State.cpp \
    StateWidget.cpp \
    Transition.cpp \
    automatonconverter.cpp \
    drawwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    minimizer.cpp \
    runautomaton.cpp \
    transitionWidget.cpp

HEADERS += \
    DFA/dfa.h \
    NFA/nfa.h \
    State.h \
    StateWidget.h \
    Transition.h \
    automatonconverter.h \
    drawwidget.h \
    mainwindow.h \
    minimizer.h \
    runautomaton.h \
    transitionWidget.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
