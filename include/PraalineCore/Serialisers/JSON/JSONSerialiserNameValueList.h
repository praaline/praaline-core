#ifndef JSONSERIALISERNAMEVALUELIST_H
#define JSONSERIALISERNAMEVALUELIST_H

/*
    Praaline - Core module - JSON Serialisers
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
#include <QJsonObject>

#include "PraalineCore/PraalineCore_Global.h"
#include "PraalineCore/Structure/NameValueList.h"
#include "PraalineCore/Serialisers/JSON/JSONSerialiserBase.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class PRAALINE_CORE_SHARED_EXPORT JSONSerialiserNameValueList : JSONSerialiserBase
{
public:
    static bool saveNameValueLists(const QList<NameValueList *> &NVLs, const QString &filename);
    static bool saveNameValueLists(const QList<NameValueList *> &NVLs, QJsonObject &json);
    static bool loadNameValueLists(QList<NameValueList *> &NVLs, const QString &filename);
    static bool loadNameValueLists(QList<NameValueList *> &NVLs, QJsonObject &json);

protected:
    JSONSerialiserNameValueList();
    ~JSONSerialiserNameValueList();

private:
    static NameValueList *readNameValueList(QJsonObject &json);
    static QJsonObject writeNameValueList(NameValueList *nvl);
};

PRAALINE_CORE_END_NAMESPACE

#endif // JSONSERIALISERNAMEVALUELIST_H
