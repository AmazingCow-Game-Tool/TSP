//Header
#include "include/ImageFinder.h"
//QT
#include <QDir>
#include <QDirIterator>
#include <QFileInfo>
#include <QDebug>
#include <QStringList>


////////////////////////////////////////////////////////////////////////////////
// CTOR                                                                       //
////////////////////////////////////////////////////////////////////////////////
ImageFinder::ImageFinder(const Options &options) :
    m_options(options)
{
    //Empty...
}


////////////////////////////////////////////////////////////////////////////////
// Public Methods                                                             //
////////////////////////////////////////////////////////////////////////////////
QVector<QString> ImageFinder::findImagesPaths()
{
    //COWTODO(n2omatt): Make the path absolute.
    //  Make sure that path exits...

    auto allowed_file_types = QStringList();
    foreach(QString file_type, m_options.allowedFiletypes)
        allowed_file_types << file_type;

    QDirIterator it(
        m_options.startPath,
        allowed_file_types,
        QDir::Files,
        QDirIterator::Subdirectories
    );

    QVector<QString> found_images;
    while(it.hasNext())
    {
        auto entry = it.next();
        qDebug() << entry;
        found_images.push_back(entry);
    }

    return found_images;
}
