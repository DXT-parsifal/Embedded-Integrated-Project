@echo off
SetLocal EnableDelayedExpansion
(set PATH=D:\hqyj\coding\STM32\MyProject\smart_homeT\Qt\build-qtmqtt-Desktop_Qt_5_9_9_MinGW_32bit-Debug\bin;D:\Qt\Qt5.9.9\5.9.9\mingw53_32\bin;!PATH!)
if defined QT_PLUGIN_PATH (
    set QT_PLUGIN_PATH=D:\Qt\Qt5.9.9\5.9.9\mingw53_32\plugins;!QT_PLUGIN_PATH!
) else (
    set QT_PLUGIN_PATH=D:\Qt\Qt5.9.9\5.9.9\mingw53_32\plugins
)
%*
EndLocal
