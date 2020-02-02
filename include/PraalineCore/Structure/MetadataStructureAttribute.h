#ifndef METADATASTRUCTUREATTRIBUTE_H
#define METADATASTRUCTUREATTRIBUTE_H

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
#include <QVariant>
#include "PraalineCore/PraalineCore_Global.h"
#include "PraalineCore/Base/DataType.h"
#include "PraalineCore/Structure/StructureAttributeBase.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class PRAALINE_CORE_SHARED_EXPORT MetadataStructureAttribute : public StructureAttributeBase
{
    Q_OBJECT
    Q_PROPERTY(bool mandatory READ mandatory WRITE setMandatory)
    Q_PROPERTY(QVariant defaultValue READ defaultValue WRITE setDefaultValue)

public:
    explicit MetadataStructureAttribute(QObject *parent = nullptr);
    MetadataStructureAttribute(const QString &ID,
                               const QString &name = QString(), const QString &description = QString(),
                               const DataType &datatype = DataType(DataType::VarChar, 255), int order = 0,
                               bool indexed = false, const QString &nameValueList = QString(),
                               bool mandatory = false, QVariant defaultValue = QVariant(),
                               QObject *parent = nullptr);
    ~MetadataStructureAttribute() override;

    MetadataStructureAttribute *clone(QObject *parent = nullptr) const override;

    // Data
    bool mandatory() const;
    void setMandatory(bool mandatory);
    QVariant defaultValue() const;
    void setDefaultValue(const QVariant &defaultValue);

    // Parent data (if available)
    QString sectionID() const;

protected:
    bool m_mandatory;
    QVariant m_defaultValue;
};

PRAALINE_CORE_END_NAMESPACE

#endif // METADATASTRUCTUREATTRIBUTE_H
