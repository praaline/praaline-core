#ifndef QUERYDEFINITION_H
#define QUERYDEFINITION_H

/*
    Praaline - Core module - Queries and Datasets
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
#include <QPair>
#include <QList>
#include "query/QueryFilterGroup.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class PRAALINE_CORE_SHARED_EXPORT QueryDefinition
{
public:
    QueryDefinition();
    ~QueryDefinition();

    int longestSequenceLength() const;

    QString name;
    QList<QueryFilterGroup> filterGroups;
    QList<QPair<QString, QString> > resultLevelsAttributes;
    int lengthContextLeft;
    int lengthContextRight;
};

PRAALINE_CORE_END_NAMESPACE

#endif // QUERYDEFINITION_H
