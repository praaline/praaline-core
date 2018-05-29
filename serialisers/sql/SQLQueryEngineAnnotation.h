#ifndef SQLQUERYENGINEANNOTATION_H
#define SQLQUERYENGINEANNOTATION_H

/*
    Praaline - Core module - SQL Serialisers
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

#include <QSqlDatabase>
#include "structure/AnnotationStructure.h"
#include "query/QueryDefinition.h"
#include "query/QueryOccurrence.h"

namespace Praaline {
namespace Core {

class SQLQueryEngineAnnotation
{
public:
    static QList<QueryOccurrencePointer *> runQuery(QueryDefinition *qdef,
                                                    AnnotationStructure *structure, QSqlDatabase &db);
    static QueryOccurrence *getOccurrence(QueryOccurrencePointer *pointer, QueryDefinition *qdef,
                                          AnnotationStructure *structure, QSqlDatabase &db,
                                          int lengthContextLeft = 10, int lengthContextRight = 10);
    static bool updateAnnotationsFromQueryOccurrences(const QList<QueryOccurrence *> &occurrences,
                                                      AnnotationStructure *structure, QSqlDatabase &db);

private:
    SQLQueryEngineAnnotation();
};

} // namespace Core
} // namespace Praaline

#endif // SQLQUERYENGINEANNOTATION_H
