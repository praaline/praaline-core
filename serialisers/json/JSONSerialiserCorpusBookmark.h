#ifndef JSONSERIALISERCORPUSBOOKMARK_H
#define JSONSERIALISERCORPUSBOOKMARK_H

/*
    Praaline - Core module - JSON Serialisers
    Copyright (c) 2011-2019 George Christodoulides

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
#include <QString>
#include <QJsonObject>

#include "pncore_global.h"
#include "JSONSerialiserBase.h"
#include "corpus/CorpusBookmark.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class PRAALINE_CORE_SHARED_EXPORT JSONSerialiserCorpusBookmark : JSONSerialiserBase
{
public:
    static bool saveCorpusBookmarks(const QList<CorpusBookmark *> &list, const QString &filename);
    static bool saveCorpusBookmarks(const QList<CorpusBookmark *> &list, QJsonObject &json);
    static bool loadCorpusBookmarks(QList<CorpusBookmark *> &list, const QString &filename);
    static bool loadCorpusBookmarks(QList<CorpusBookmark *> &list, QJsonObject &json);

protected:
    JSONSerialiserCorpusBookmark();
    ~JSONSerialiserCorpusBookmark();

private:
    static CorpusBookmark *readBookmark(QJsonObject &json);
    static QJsonObject writeBookmark(CorpusBookmark *bookmark);
};

PRAALINE_CORE_END_NAMESPACE

#endif // JSONSERIALISERCORPUSBOOKMARK_H
