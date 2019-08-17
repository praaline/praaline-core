#ifndef METADATASTRUCTURESECTION_H
#define METADATASTRUCTURESECTION_H

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
#include "structure/MetadataStructureAttribute.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class PRAALINE_CORE_SHARED_EXPORT MetadataStructureSection : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString ID READ ID WRITE setID)
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QString description READ description WRITE setDescription)
    Q_PROPERTY(int itemOrder READ itemOrder WRITE setItemOrder)

public:
    explicit MetadataStructureSection(QObject *parent = nullptr);
    MetadataStructureSection(const QString &ID, const QString &name = QString(),
                             const QString &description = QString(), int itemOrder = 0, QObject *parent = nullptr);
    ~MetadataStructureSection();

    // Data
    QString ID() const;
    void setID(const QString &id);
    QString name() const;
    void setName(const QString &name);
    QString description() const;
    void setDescription(const QString &description);
    int itemOrder() const;
    void setItemOrder(int itemOrder);

    // METADATA ATTRIBUTES
    // Accessors
    MetadataStructureAttribute *attribute(int index) const;
    MetadataStructureAttribute *attribute(const QString &ID) const;
    int attributeIndexByID(const QString &ID) const;
    int attributesCount() const;
    bool hasAttributes() const;
    bool hasAttribute(const QString &ID) const;
    QStringList attributeIDs() const;
    QStringList attributeNames() const;
    QList<MetadataStructureAttribute *> attributes() const;
    // Mutators
    bool insertAttribute(int index, MetadataStructureAttribute *attribute);
    bool addAttribute(MetadataStructureAttribute *attribute);
    void swapAttribute(int oldIndex, int newIndex);
    void removeAttributeAt(int i);
    void removeAttributeByID(const QString &ID);
    void clear();

signals:
    void attributeAdded(MetadataStructureSection *section, MetadataStructureAttribute *attribute);
    void attributeDeleted(MetadataStructureSection *section, QString attributeID);

protected:
    QString m_ID;           // Section ID (e.g. speaker)
    QString m_name;         // User-friendly name (e.g. Speaker)
    QString m_description;  // Description (e.g. Speakers metadata)
    int m_itemOrder;        // Order for presentation purposes
    QList<MetadataStructureAttribute *> m_attributes;
};

PRAALINE_CORE_END_NAMESPACE

#endif // METADATASTRUCTURESECTION_H
