TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lcurl

SOURCES += \
        NetworkManager.cpp \
        Request.cpp \
        RequestHtml.cpp \
        main.cpp

HEADERS += \
    NetworkManager.h \
    Request.h \
    RequestHtml.h
