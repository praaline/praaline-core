#ifndef SQLSERIALISERSYSTEM_H
#define SQLSERIALISERSYSTEM_H

/*
    Praaline - Core module - SQL Serialisers
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

#include <QString>

#include "pncore_global.h"
#include "corpus/CorpusObject.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class SQLSerialiserSystem
{
public:
    static QString tableNameForCorpusObjectType(CorpusObject::Type type);
    static CorpusObject::Type corpusObjectTypeFromCode(const QString &code);
    static QString corpusObjectCodeFromType(const CorpusObject::Type type);
    static QString defaultSectionID(const CorpusObject::Type type);

private:
    SQLSerialiserSystem() {}
};

PRAALINE_CORE_END_NAMESPACE

#endif // SQLSERIALISERSYSTEM_H
