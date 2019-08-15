#ifndef XMLSERIALISERNAMEVALUELIST_H
#define XMLSERIALISERNAMEVALUELIST_H

/*
    Praaline - Core module - XML Serialisers
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
#include <QPointer>
#include <QString>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

#include "pncore_global.h"
#include "XMLSerialiserBase.h"
#include "structure/NameValueList.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class PRAALINE_CORE_SHARED_EXPORT XMLSerialiserNameValueList : XMLSerialiserBase
{
public:
    static bool saveNameValueLists(const QList<QPointer<NameValueList> > &NVLs, const QString &filename);
    static bool saveNameValueLists(const QList<QPointer<NameValueList> > &NVLs, QXmlStreamWriter &xml);
    static bool loadNameValueLists(QList<QPointer<NameValueList> > &NVLs, const QString &filename);
    static bool loadNameValueLists(QList<QPointer<NameValueList> > &NVLs, QXmlStreamReader &xml);

private:
    XMLSerialiserNameValueList();
    ~XMLSerialiserNameValueList();

    static NameValueList *readNameValueList(QXmlStreamReader &xml);
    static bool writeNameValueList(NameValueList *nvl, QXmlStreamWriter &xml);

    static QString xmlElementName_NameValueList;
};

PRAALINE_CORE_END_NAMESPACE

#endif // XMLSERIALISERNAMEVALUELIST_H
