QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# QTITANDIR路径
QTITANDIR = D:\Project_3D_Slice\Qt\QtitanRibbon6.5.0

include($$QTITANDIR\src\shared\qtitanstyle.pri)
include($$QTITANDIR\src\shared\qtitanfastinfoset.pri)
include($$QTITANDIR\src\shared\qtitanribbon.pri)

#Osg库的路径
OSGDIR = $$PWD\third_part\OpenSceneGraph-3.6.5-VC2019-64-Debug

INCLUDEPATH += $$OSGDIR/include
LIBS += -L$$OSGDIR/lib \ 
    -losgd \
    -losgDBd \
    -losgGAd \
    -losgQt5d \
    -losgViewerd

DESTDIR = $$quote($$PWD\build\Debug)

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    OsgWidget.cpp

HEADERS += \
    mainwindow.h \
    OsgWidget.h

FORMS += \
    mainwindow.ui

#RESOURCES += res.qrc

include($$PWD/third_part/ribbon/aboutdialog/aboutdialog.pri)
include($$PWD/third_part/ribbon/DemoRibbonWindow/DemoRibbonWindow.pri)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
