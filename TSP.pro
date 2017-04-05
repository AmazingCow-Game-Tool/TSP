TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
QT += core
QT += gui


SOURCES += $$system("find . -name '*.cpp'")
HEADERS += $$system("find . -name '*.h'")


