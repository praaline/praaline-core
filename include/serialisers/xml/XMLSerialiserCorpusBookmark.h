#ifndef XMLSERIALISERCORPUSBOOKMARK_H
#define XMLSERIALISERCORPUSBOOKMARK_H

/*
    Praaline - Core module - XML Serialisers
    Copyright (c) 2011-2018 George Christodoulides

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
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

#include "pncore_global.h"
#include "corpus/CorpusBookmark.h"
#include "serialisers/xml/XMLSerialiserBase.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class PRAALINE_CORE_SHARED_EXPORT XMLSerialiserCorpusBookmark : XMLSerialiserBase
{
public:
    static bool saveCorpusBookmarks(const QList<CorpusBookmark *> &list, const QString &filename);
    static bool saveCorpusBookmarks(const QList<CorpusBookmark *> &list, QXmlStreamWriter &xml);
    static bool loadCorpusBookmarks(QList<CorpusBookmark *> &list, const QString &filename);
    static bool loadCorpusBookmarks(QList<CorpusBookmark *> &list, QXmlStreamReader &xml);

protected:
    XMLSerialiserCorpusBookmark();
    ~XMLSerialiserCorpusBookmark();

private:
    static CorpusBookmark *readBookmark(QXmlStreamReader &xml);
    static bool writeBookmark(CorpusBookmark *bookmark, QXmlStreamWriter &xml);

    static QString xmlElementName_CorpusBookmark;
};

PRAALINE_CORE_END_NAMESPACE

#endif // XMLSERIALISERCORPUSBOOKMARK_H
