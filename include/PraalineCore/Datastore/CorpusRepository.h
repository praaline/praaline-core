#ifndef CORPUSREPOSITORY_H
#define CORPUSREPOSITORY_H

/*
    Praaline - Core module - Datastores
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
#include "PraalineCore/PraalineCore_Global.h"
#include "PraalineCore/Base/DataType.h"
#include "PraalineCore/Corpus/CorpusObjectInfo.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class CorpusRepositoryDefinition;
class MetadataDatastore;
class AnnotationDatastore;
class FileDatastore;
class MetadataStructure;
class AnnotationStructure;

struct CorpusRepositoryData;

class PRAALINE_CORE_SHARED_EXPORT CorpusRepository : public QObject
{
    Q_OBJECT
public:
    // Corpus repository
    // ==========================================================================================================================
    static CorpusRepository *create(const CorpusRepositoryDefinition &definition, QString &errorMessages, QObject *parent = nullptr);
    static CorpusRepository *open(const CorpusRepositoryDefinition &definition, QString &errorMessages, QObject *parent = nullptr);
    void close();

    QString ID() const;
    void setID(const QString &ID);
    QString description() const;
    void setDescription(const QString &description);
    void setBasePathMedia(const QString &path);

    CorpusRepositoryDefinition definition() const;

    // Datastores
    // ==========================================================================================================================
    AnnotationDatastore *annotations() const;
    MetadataDatastore *metadata() const;
    FileDatastore *files() const;
    QList<CorpusObjectInfo> listCorporaInfo() const;
    QStringList listCorporaIDs() const;

    // Metadata and Annotation structures
    // ==========================================================================================================================
    MetadataStructure *metadataStructure() const;
    AnnotationStructure *annotationStructure() const;
    void importMetadataStructure(MetadataStructure *otherStructure);
    void importAnnotationStructure(AnnotationStructure *otherStructure);
    bool createMetadataAttribute(CorpusObject::Type type, const QString &sectionID, const QString &ID, const QString &name = QString(),
                                 const QString &description = QString(), const DataType &datatype = DataType(DataType::VarChar, 256),
                                 int order = 0, bool indexed = false, const QString &nameValueList = QString());
    bool createAnnotationAttribute(const QString &annotationLevelID, const QString &ID, const QString &name = QString(),
                                   const QString &description = QString(), const DataType &datatype = DataType(DataType::VarChar, 256),
                                   int order = 0, bool indexed = false, const QString &nameValueList = QString());

    // Error handling and logging
    // ==========================================================================================================================
    QString lastError() const;
    void setLastError(const QString &errorMessage);
    void clearLastError();
    void sendLogMessage(const QString &category, const QString &message);

signals:
    void changedID(const QString &oldID, const QString &newID);
    void logMessage(const QString &category, const QString &message);

public slots:

public:
    ~CorpusRepository();

private:
    CorpusRepository(const CorpusRepositoryDefinition &definition, QObject *parent = nullptr);

    CorpusRepositoryData *d;
};

PRAALINE_CORE_END_NAMESPACE

#endif // CORPUSREPOSITORY_H
