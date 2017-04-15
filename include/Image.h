#pragma once

//QT
#include <QtCore>
#include <QtGui>

class Image
{
    // Static Methods //
public:
    static Image LoadFromFile(const QString &filePath);



    // Public Methods //
public:
    const QString& getPath    () const;
    const QString  getBasename() const;
    const QString  getFilename() const;

    const QSize&  getSize  () const;
    const QImage& getQImage() const;


    // iVars //
public:
    QString m_path;
    QSize   m_size;
    QImage  m_image;
};

