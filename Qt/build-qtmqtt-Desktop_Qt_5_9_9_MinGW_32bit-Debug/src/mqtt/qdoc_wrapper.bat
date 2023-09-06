@echo off
SetLocal EnableDelayedExpansion
(set QT_VERSION=5.15.3)
(set QT_VER=5.15)
(set QT_VERSION_TAG=5153)
(set QT_INSTALL_DOCS=D:/Qt/Qt5.9.9/Docs/Qt-5.9.9)
(set BUILDDIR=D:/hqyj/coding/STM32/MyProject/smart_homeT/Qt/build-qtmqtt-Desktop_Qt_5_9_9_MinGW_32bit-Debug/src/mqtt)
D:\Qt\Qt5.9.9\5.9.9\mingw53_32\bin\qdoc.exe %*
EndLocal
