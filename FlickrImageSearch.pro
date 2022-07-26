QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/filedownloader.cpp \
    src/flickrapi.cpp \
    src/flickrimageurl.cpp \
    src/imageviewer.cpp \
    src/main.cpp \
    src/flickrsearchmainwindow.cpp \
    src/restapi/flickrrestclient.cpp

HEADERS += \
    src/flickrapi.h \
    src/flickrimageurl.h \
    src/flickrsearchmainwindow.h \
    src/imageviewer.h \
    src/filedownloader.h \
    src/restapi/flickrrestclient.h

FORMS += \
    ui/flickrsearchmainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/resources.qrc

DISTFILES += \
    resources/icons/FlickrImageSearch.ico \
    resources/icons/FlickrImageSearch.png \
    resources/icons/FlipH.svg \
    resources/icons/FlipV.svg \
    resources/icons/go-next.svg \
    resources/icons/go-previous.svg \
    resources/icons/loading.png \
    resources/icons/object-rotate-left.svg \
    resources/icons/object-rotate-right.svg \
    resources/icons/transform-crop.svg \
    resources/icons/zoom-in.svg \
    resources/icons/zoom-out.svg
