#ifndef ANNOTATIONSTRUCTURELEVEL_H
#define ANNOTATIONSTRUCTURELEVEL_H

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
#include <QList>
#include <QString>
#include <QStringList>
#include "PraalineCore/PraalineCore_Global.h"
#include "PraalineCore/Structure/StructureAttributeBase.h"
#include "PraalineCore/Structure/AnnotationStructureAttribute.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class PRAALINE_CORE_SHARED_EXPORT AnnotationStructureLevel : public StructureAttributeBase
{
    Q_OBJECT
    Q_PROPERTY(LevelType levelType READ levelType WRITE setLevelType)
    Q_PROPERTY(QString parentLevelID READ parentLevelID WRITE setParentLevelID)

public:
    enum LevelType {
        IndependentPointsLevel    = 10,
        IndependentIntervalsLevel = 20,
        GroupingLevel             = 30,
        SequencesLevel            = 40,
        TreeLevel                 = 50,
        RelationsLevel            = 60
    };
    Q_ENUM(LevelType)

    explicit AnnotationStructureLevel(QObject *parent = nullptr);
    AnnotationStructureLevel(const QString &ID, LevelType type = IndependentIntervalsLevel,
                             const QString &name = QString(), const QString &description = QString(),
                             const QString &parentLevelID = QString(),
                             const DataType &datatype = DataType(DataType::VarChar, 1024),
                             int order = 0, bool indexed = false, const QString &nameValueList = QString(),
                             QObject *parent = nullptr);
    ~AnnotationStructureLevel() override;

    // DATA
    LevelType levelType() const;
    bool isLevelTypePrimary() const;
    bool isLevelTypeDerived() const;
    void setLevelType(LevelType type);
    QString parentLevelID() const;
    void setParentLevelID(const QString &parentLevelID);

    // ANNOTATION ATTRIBUTES
    // Accessors
    AnnotationStructureAttribute *attribute(int index) const;
    AnnotationStructureAttribute *attribute(const QString &ID) const;
    int attributeIndexByID(const QString &ID) const;
    int attributesCount() const;
    bool hasAttributes() const;
    bool hasAttribute(const QString &ID) const;
    QStringList attributeIDs() const;
    QStringList attributeNames() const;
    QList<AnnotationStructureAttribute *> attributes() const;
    // Mutators
    bool insertAttribute(int index, AnnotationStructureAttribute *attribute);
    bool addAttribute(AnnotationStructureAttribute *attribute);
    void swapAttribute(int oldIndex, int newIndex);
    void removeAttributeAt(int i);
    void removeAttributeByID(const QString &ID);
    void clear();

signals:
    void attributeAdded(AnnotationStructureLevel *level, AnnotationStructureAttribute *attribute);
    void attributeDeleted(AnnotationStructureLevel *level, QString attributeID);
    
protected:
    LevelType m_levelType;      // Level type (e.g. independent or grouping)
    QString m_parentLevelID;    // Parent level ID for grouping levels (e.g. phone for syll)
    QList<AnnotationStructureAttribute *> m_attributes;
};

PRAALINE_CORE_END_NAMESPACE

#endif // ANNOTATIONSTRUCTURELEVEL_H

