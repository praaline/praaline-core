#ifndef ANNOTATIONSTRUCTUREATTRIBUTE_H
#define ANNOTATIONSTRUCTUREATTRIBUTE_H

/*
    Praaline - Core module - Corpus Structure Definition
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
#include "praaline-core_global.h"
#include "base/DataType.h"
#include "structure/StructureAttributeBase.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class PRAALINE_CORE_SHARED_EXPORT AnnotationStructureAttribute : public StructureAttributeBase
{
    Q_OBJECT
    Q_PROPERTY(QString statLevelOfMeasurement READ statLevelOfMeasurement  WRITE setStatLevelOfMeasurement)

public:
    explicit AnnotationStructureAttribute(QObject *parent = nullptr);
    AnnotationStructureAttribute(const QString &ID,
                                 const QString &name = QString(), const QString &description = QString(),
                                 const DataType &datatype = DataType(DataType::VarChar, 255), int order = 0,
                                 bool indexed = false, const QString &nameValueList = QString(),
                                 const QString &statLevelOfMeasurement = QString(),
                                 QObject *parent = nullptr);
    ~AnnotationStructureAttribute() override;

    AnnotationStructureAttribute *clone(QObject *parent = nullptr) const override;

    // Data
    QString statLevelOfMeasurement() const;
    void setStatLevelOfMeasurement(const QString &statLevelOfMeasurement);

protected:
    QString m_statLevelOfMeasurement;
};

PRAALINE_CORE_END_NAMESPACE

#endif // CORPUSANNOTATIONATTRIBUTE_H
