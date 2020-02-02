#ifndef FILEDATASTORE_H
#define FILEDATASTORE_H

/*
    Praaline - Core module - Datastores
    Copyright (c) 2011-2020 George Christodoulides

    This program or module is free software: you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation, either version 3 of
    the License, or (at your option) any later version. It is provided
    for educational purposes and is distributed in the hope that it will
    be useful, but WITHOUT ANY WARRANTY; without even the implied
    warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See
    the GNU General Public License for more details.
*/

#include <QObject>
#include "PraalineCore/PraalineCore_Global.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class Corpus;
class CorpusObjectInfo;

class PRAALINE_CORE_SHARED_EXPORT FileDatastore : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString basePath READ basePath WRITE setBasePath)

public:
    explicit FileDatastore(QObject *parent = nullptr);
    virtual ~FileDatastore() {}

    QString basePath() const { return m_basePath; }
    void setBasePath(const QString &path);

    QString getRelativeToBasePath (const QString &absoluteFilePath) const;

protected:
    QString m_basePath;
};

PRAALINE_CORE_END_NAMESPACE

#endif // FILEDATASTORE_H
