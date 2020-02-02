#ifndef QUERYFILTERGROUP_H
#define QUERYFILTERGROUP_H

/*
    Praaline - Core module - Queries and Datasets
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

#include <QString>
#include <QList>
#include "PraalineCore/PraalineCore_Global.h"
#include "PraalineCore/Query/QueryFilterSequence.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class PRAALINE_CORE_SHARED_EXPORT QueryFilterGroup
{
public:
    QueryFilterGroup();
    ~QueryFilterGroup();

    QString name;
    QList<QueryFilterSequence> filterSequences;

    int longestSequenceLength() const;
};

PRAALINE_CORE_END_NAMESPACE

#endif // QUERYFILTERGROUP_H
