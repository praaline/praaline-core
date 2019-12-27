#ifndef NAMEVALUELISTDATASTORE_H
#define NAMEVALUELISTDATASTORE_H

/*
    Praaline - Core module - Datastores
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

#include "pncore_global.h"
#include <QString>
#include <QMap>

PRAALINE_CORE_BEGIN_NAMESPACE

class NameValueList;

// internal interface
class PRAALINE_CORE_SHARED_EXPORT NameValueListDatastore
{
public:
    NameValueListDatastore();
    virtual ~NameValueListDatastore();

    virtual NameValueList *getNameValueList(const QString &listID) = 0;
    virtual QStringList getAllNameValueListIDs() = 0;
    virtual QMap<QString, NameValueList *> getAllNameValueLists() = 0;
    virtual bool createNameValueList(NameValueList *list) = 0;
    virtual bool updateNameValueList(NameValueList *list) = 0;
    virtual bool deleteNameValueList(const QString &listID) = 0;
};

PRAALINE_CORE_END_NAMESPACE

#endif // NAMEVALUELISTDATASTORE_H
