#ifndef QUERYFILTERSEQUENCE_H
#define QUERYFILTERSEQUENCE_H

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
#include <QVariant>
#include "PraalineCore/PraalineCore_Global.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class PRAALINE_CORE_SHARED_EXPORT QueryFilterSequence
{
public:
    explicit QueryFilterSequence(QString annotationLevelID);
    ~QueryFilterSequence();

    enum Operand {
        NoCondition,
        Equals,
        DoesNotEqual,
        GreaterThan,
        GreaterThanOrEqual,
        LessThan,
        LessThanOrEqual,
        Contains,
        DoesNotContain,
        Like
    };

    struct Condition {
        Condition(Operand operand, QVariant value) : operand(operand), value(value)
        {}
        Operand operand;
        QVariant value;
    };

    QString annotationLevelID() const;
    QStringList attributeIDs() const;
    int attributesCount() const;
    int sequenceLength() const;
    Condition condition(QString annotationAttributeID, int position) const;
    void setCondition(QString annotationAttributeID, int position, Condition condition);
    QString conditionString(QString annotationAttributeID, int position) const;
    void setConditionString(QString annotationAttributeID, int position, QString whereClause);
    void addAttribute(QString annotationAttributeID);
    void removeAttribute(QString annotationAttributeID);
    void expandSequence(int length = 1);
    void reduceSequence(int length = 1);
    QString friendlySyntax() const;

private:
    QString m_annotationLevelID;
    QMap<QString, QList<Condition> > m_conditions;
};

PRAALINE_CORE_END_NAMESPACE

#endif // QUERYFILTERSEQUENCE_H
