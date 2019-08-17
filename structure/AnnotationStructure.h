#ifndef ANNOTATIONSTRUCTURE_H
#define ANNOTATIONSTRUCTURE_H

/*
    Praaline - Core module - Corpus Structure Definition
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
#include <QObject>
#include <QString>
#include <QList>
#include "structure/AnnotationStructureLevel.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class PRAALINE_CORE_SHARED_EXPORT AnnotationStructure : public QObject
{
    Q_OBJECT
public:
    explicit AnnotationStructure(QObject *parent = nullptr);
    ~AnnotationStructure() override;

    // DATA
    QString ID() const;
    void setID(const QString &ID);

    // ANNOTATION LEVELS
    // Accessors
    AnnotationStructureLevel *level(int index) const;
    AnnotationStructureLevel *level(const QString &ID) const;
    int levelIndexByID(const QString &ID) const;
    int levelsCount() const;
    bool hasLevels() const;
    bool hasLevel(const QString &ID) const;
    QStringList levelIDs() const;
    QList<AnnotationStructureLevel *> levels() const;
    // Mutators
    bool insertLevel(int index, AnnotationStructureLevel *level);
    bool addLevel(AnnotationStructureLevel *level);
    void swapLevels(int oldIndex, int newIndex);
    void removeLevelAt(int i);
    void removeLevelByID(const QString &ID);
    void clear();

signals:
    void levelAdded(AnnotationStructure *structure, AnnotationStructureLevel *level);
    void levelDeleted(AnnotationStructure *structure, QString levelID);

protected:
    QString m_ID;
    QList<AnnotationStructureLevel *> m_levels;
};

PRAALINE_CORE_END_NAMESPACE

#endif // ANNOTATIONSTRUCTURE_H
