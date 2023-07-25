TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lcurl

SOURCES += \
        ImageUploader.cpp \
        NetworkManager.cpp \
        Request.cpp \
        RequestHtml.cpp \
        main.cpp

HEADERS += \
    ImageUploader.h \
    NetworkManager.h \
    Request.h \
    RequestHtml.h
