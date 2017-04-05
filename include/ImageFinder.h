#pragma once

//QT
#include <QString>
#include <QVector>

class ImageFinder
{
    // Inner Types //
public:
    struct Options
    {
        QString          startPath;
        QVector<QString> ignorePaths;
        QVector<QString> allowedFiletypes;
    };


    // CTOR //
public:
    ImageFinder(const Options &options);


    // Public Methods//
public:
    QVector<QString> findImagesPaths();


    // iVars //
private:
    Options          m_options;
    QVector<QString> m_imagePaths;
};
