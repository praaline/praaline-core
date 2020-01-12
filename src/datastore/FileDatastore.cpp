#include <QString>
#include <QDir>
#include "datastore/FileDatastore.h"

PRAALINE_CORE_BEGIN_NAMESPACE

FileDatastore::FileDatastore(QObject *parent) :
    QObject(parent)
{
}

void FileDatastore::setBasePath(const QString &path)
{
    m_basePath = QDir(path).absolutePath();
}

QString FileDatastore::getRelativeToBasePath(const QString &absoluteFilePath) const
{
    if (m_basePath.isEmpty())
        return absoluteFilePath;
    return QDir(QDir(m_basePath).canonicalPath()).relativeFilePath(absoluteFilePath);
}

PRAALINE_CORE_END_NAMESPACE

