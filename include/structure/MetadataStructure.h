#ifndef METADATASTRUCTURE_H
#define METADATASTRUCTURE_H

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
#include <QHash>
#include "corpus/CorpusObject.h"
#include "structure/MetadataStructureSection.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class PRAALINE_CORE_SHARED_EXPORT MetadataStructure : public QObject
{
    Q_OBJECT
public:
    explicit MetadataStructure(QObject *parent = nullptr);
    ~MetadataStructure();

    QString ID() const { return m_ID; }
    void setID(const QString &ID) { m_ID = ID; }

    // METADATA STRUCTURE SECTIONS by OBJECT
    MetadataStructureSection *section(CorpusObject::Type what, int index) const;
    MetadataStructureSection *section(CorpusObject::Type what, const QString &ID) const;
    int sectionIndexByID(CorpusObject::Type what, const QString &ID) const;
    int sectionsCount(CorpusObject::Type what) const;
    bool hasSections(CorpusObject::Type what) const;
    bool hasSection(CorpusObject::Type what, const QString &ID) const;
    QList<MetadataStructureSection *> sections(CorpusObject::Type what) const;
    bool insertSection(CorpusObject::Type what, int index, MetadataStructureSection *section);
    bool addSection(CorpusObject::Type what, MetadataStructureSection *section);
    void swapSections(CorpusObject::Type what, int oldIndex, int newIndex);
    void removeSectionAt(CorpusObject::Type what, int i);
    void removeSectionByID(CorpusObject::Type what, const QString &ID);
    void clear(CorpusObject::Type what);
    void clearAll();
    // Direct access to attributes
    MetadataStructureAttribute *attribute(CorpusObject::Type what, const QString &ID) const;
    QList<MetadataStructureAttribute *> attributes(CorpusObject::Type what) const;
    QStringList attributeIDs(CorpusObject::Type what) const;
    QStringList attributeNames(CorpusObject::Type what) const;
    CorpusObject::Type corpusObjectTypeOfSection(MetadataStructureSection *section) const;
    // Defaults
    static QString defaultSectionID(CorpusObject::Type type);
    static QStringList basicAttributeIDs(CorpusObject::Type type);
    static QStringList basicAttributeNames(CorpusObject::Type type);
    QStringList allAttributeIDs(CorpusObject::Type what) const;
    QStringList allAttributeNames(CorpusObject::Type what) const;

signals:
    void sectionAdded(MetadataStructure *structure, CorpusObject::Type what, MetadataStructureSection *section);
    void sectionDeleted(MetadataStructure *structure, CorpusObject::Type what, QString sectionID);

protected:
    QString m_ID;
    QHash<CorpusObject::Type, QList<MetadataStructureSection *> > m_sections;

private:
    void createDefaultSection(CorpusObject::Type what);
    bool replaceDefaultSection(CorpusObject::Type what, MetadataStructureSection *section);
};

PRAALINE_CORE_END_NAMESPACE

#endif // METADATASTRUCTURE_H
