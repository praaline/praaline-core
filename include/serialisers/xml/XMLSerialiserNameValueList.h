#ifndef XMLSERIALISERNAMEVALUELIST_H
#define XMLSERIALISERNAMEVALUELIST_H

/*
    Praaline - Core module - XML Serialisers
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
#include <QString>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

#include "praaline-core_global.h"
#include "structure/NameValueList.h"
#include "serialisers/xml/XMLSerialiserBase.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class PRAALINE_CORE_SHARED_EXPORT XMLSerialiserNameValueList : XMLSerialiserBase
{
public:
    static bool saveNameValueLists(const QList<NameValueList *> &NVLs, const QString &filename);
    static bool saveNameValueLists(const QList<NameValueList *> &NVLs, QXmlStreamWriter &xml);
    static bool loadNameValueLists(QList<NameValueList *> &NVLs, const QString &filename);
    static bool loadNameValueLists(QList<NameValueList *> &NVLs, QXmlStreamReader &xml);

protected:
    XMLSerialiserNameValueList();
    ~XMLSerialiserNameValueList();

private:
    static NameValueList *readNameValueList(QXmlStreamReader &xml);
    static bool writeNameValueList(NameValueList *nvl, QXmlStreamWriter &xml);

    static QString xmlElementName_NameValueList;
};

PRAALINE_CORE_END_NAMESPACE

#endif // XMLSERIALISERNAMEVALUELIST_H
