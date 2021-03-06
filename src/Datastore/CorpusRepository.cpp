#include <QObject>
#include <QPointer>
#include <QString>
#include <QList>
#include <QMetaEnum>
#include <QRegularExpression>

#include "PraalineCore/Structure/MetadataStructure.h"
#include "PraalineCore/Structure/AnnotationStructure.h"
#include "PraalineCore/Datastore/CorpusRepositoryDefinition.h"
#include "PraalineCore/Datastore/DatastoreFactory.h"
#include "PraalineCore/Datastore/MetadataDatastore.h"
#include "PraalineCore/Datastore/AnnotationDatastore.h"
#include "PraalineCore/Datastore/FileDatastore.h"
#include "PraalineCore/Datastore/CorpusRepository.h"

PRAALINE_CORE_BEGIN_NAMESPACE

struct CorpusRepositoryData {
    CorpusRepositoryDefinition definition;
    QPointer<MetadataStructure> metadataStructure;
    QPointer<AnnotationStructure> annotationStructure;
    QPointer<MetadataDatastore> datastoreMetadata;
    QPointer<AnnotationDatastore> datastoreAnnotations;
    QPointer<FileDatastore> datastoreFiles;
    QString lastError;
};

CorpusRepository::CorpusRepository(const CorpusRepositoryDefinition &definition, QObject *parent) :
    QObject(parent), d(new CorpusRepositoryData)
{
    d->annotationStructure = new AnnotationStructure(this);
    d->metadataStructure = new MetadataStructure(this);
    d->datastoreAnnotations = DatastoreFactory::getAnnotationDatastore(definition.infoDatastoreAnnotations, d->annotationStructure, this);
    d->datastoreMetadata = DatastoreFactory::getMetadataDatastore(definition.infoDatastoreMetadata, d->metadataStructure, this);
    d->datastoreFiles = new FileDatastore(this);
    d->definition = definition;
}

CorpusRepository::~CorpusRepository()
{
    if (d->datastoreMetadata)    delete d->datastoreMetadata;
    if (d->datastoreAnnotations) delete d->datastoreAnnotations;
    if (d->datastoreFiles)       delete d->datastoreFiles;
    if (d->metadataStructure)    delete d->metadataStructure;
    if (d->annotationStructure)  delete d->annotationStructure;
    delete d;
}

// static
CorpusRepository *CorpusRepository::create(const CorpusRepositoryDefinition &definition, QString &errorMessages, QObject *parent)
{
    errorMessages.clear();
    CorpusRepository *repository = new CorpusRepository(definition, parent);
    if (repository->annotations()) {
        if (!repository->annotations()->createDatastore(definition.infoDatastoreAnnotations)) {
            errorMessages.append("Error creating annotation datastore: ").append(repository->lastError()).append("\n");
            repository->clearLastError();
        }
    }
    if (repository->metadata()) {
        if (!repository->metadata()->createDatastore(definition.infoDatastoreMetadata)) {
            errorMessages.append("Error creating metadata datastore: ").append(repository->lastError()).append("\n");
            repository->clearLastError();
        }
    }
    if (repository->files()) {
        repository->files()->setBasePath(definition.basePathMedia);
    }
    return repository;
}

// static
CorpusRepository *CorpusRepository::open(const CorpusRepositoryDefinition &definition, QString &errorMessages, QObject *parent)
{
    errorMessages.clear();
    QPointer<CorpusRepository> repository = new CorpusRepository(definition, parent);
    if (repository->annotations()) {
        if (!repository->annotations()->openDatastore(definition.infoDatastoreAnnotations)) {
            errorMessages.append("Error opening annotation datastore: ").append(repository->lastError()).append("\n");
            repository->clearLastError();
            return nullptr;
        }
        if (!repository->annotations()->loadAnnotationStructure()) {
            errorMessages.append("Error reading annotation structure: ").append(repository->lastError()).append("\n");
            repository->clearLastError();
            return nullptr;
        }
    }
    if (repository->metadata()) {
        if (!repository->metadata()->openDatastore(definition.infoDatastoreMetadata)) {
            errorMessages.append("Error opening metadata datastore: ").append(repository->lastError()).append("\n");
            repository->clearLastError();
            return nullptr;
        }
        if (!repository->metadata()->loadMetadataStructure()) {
            errorMessages.append("Error reading metadata structure: ").append(repository->lastError()).append("\n");
            repository->clearLastError();
            return nullptr;
        }
    }
    if (repository->files()) {
        repository->files()->setBasePath(definition.basePathMedia);
    }
    return repository;
}

void CorpusRepository::close()
{
    d->datastoreMetadata->closeDatastore();
    d->datastoreAnnotations->closeDatastore();
}

QString CorpusRepository::ID() const
{
    return d->definition.repositoryID;
}

void CorpusRepository::setID(const QString &ID)
{
    QString oldID = d->definition.repositoryID;
    d->definition.repositoryID = ID;
    emit changedID(oldID, ID);
}

QString CorpusRepository::description() const
{
    return d->definition.repositoryName;
}

void CorpusRepository::setDescription(const QString &description)
{
    d->definition.repositoryName = description;
}

CorpusRepositoryDefinition CorpusRepository::definition() const
{
    return d->definition;
}

void CorpusRepository::setBasePathMedia(const QString &path)
{
    if (d->datastoreFiles) {
        d->definition.basePathMedia = path;
        d->datastoreFiles->setBasePath(path);
    }
}

// ==============================================================================================================================
// Datastores
// ==============================================================================================================================

AnnotationDatastore *CorpusRepository::annotations() const
{
    return d->datastoreAnnotations;
}

MetadataDatastore *CorpusRepository::metadata() const
{
    return d->datastoreMetadata;
}

FileDatastore *CorpusRepository::files() const
{
    return d->datastoreFiles;
}

QList<CorpusObjectInfo> CorpusRepository::listCorporaInfo() const
{
    QList<CorpusObjectInfo> list;
    if (d->datastoreMetadata)
        list = d->datastoreMetadata->getCorpusObjectInfoList(CorpusObject::Type_Corpus,
                                                             MetadataDatastore::Selection("", "", ""));
    if (list.isEmpty()) {
        // Probably old-style database with only one corpus
        CorpusObjectInfo corpusInfo(CorpusObject::Type_Corpus);
        corpusInfo.setAttribute("corpusID", ID());
        list << corpusInfo;
    }
    return list;
}

QStringList CorpusRepository::listCorporaIDs() const
{
    QStringList ret;
    foreach (CorpusObjectInfo info, listCorporaInfo()) {
        ret << info.attribute("corpusID").toString();
    }
    return ret;
}

// ==============================================================================================================================
// Metadata and annotation structures
// ==============================================================================================================================

MetadataStructure *CorpusRepository::metadataStructure() const
{
    return d->metadataStructure;
}

AnnotationStructure *CorpusRepository::annotationStructure() const
{
    return d->annotationStructure;
}

bool CorpusRepository::createMetadataAttribute(CorpusObject::Type type, const QString &sectionID, const QString &ID, const QString &name,
                                               const QString &description, const DataType &datatype,
                                               int order, bool indexed, const QString &nameValueList)
{
    Q_UNUSED(indexed)
    Q_UNUSED(nameValueList)
    if (!d->datastoreMetadata) return false;
    if (!d->metadataStructure) return false;
    QString effectiveSectionID = sectionID;
    if (effectiveSectionID.isEmpty()) effectiveSectionID = d->metadataStructure->defaultSectionID(type);
    MetadataStructureSection *section = d->metadataStructure->section(type, effectiveSectionID);
    if (!section) {
        section = new MetadataStructureSection(sectionID, sectionID);
        d->metadataStructure->addSection(type, section);
    }
    if (section->hasAttribute(ID)) return false; // already exists
    MetadataStructureAttribute *attr = new MetadataStructureAttribute(ID, name, description, datatype,
                                                                      order);
    if (d->datastoreMetadata->createMetadataAttribute(type, attr)) {
        section->addAttribute(attr);
        return true;
    }
    return false;
}

bool CorpusRepository::createAnnotationAttribute(const QString &annotationLevelID, const QString &ID, const QString &name,
                                                 const QString &description, const DataType &datatype,
                                                 int order, bool indexed, const QString &nameValueList)
{
    if (!d->datastoreAnnotations) return false;
    if (!d->annotationStructure) return false;
    AnnotationStructureLevel *level = d->annotationStructure->level(annotationLevelID);
    if (!level) return false; // level does not exist
    if (level->hasAttribute(ID)) return false; // already exists
    AnnotationStructureAttribute *attr = new AnnotationStructureAttribute(ID, name, description, datatype,
                                                                          order, indexed, nameValueList);
    if (d->datastoreAnnotations->createAnnotationAttribute(level->ID(), attr)) {
        level->addAttribute(attr);
        return true;
    }
    return false;
}

void CorpusRepository::importMetadataStructure(MetadataStructure *otherStructure)
{
    if (!d->datastoreMetadata) return;
    if (!d->metadataStructure) return;

    std::vector<QString> errors;

    const QMetaObject &mo = CorpusObject::staticMetaObject;
    int index = mo.indexOfEnumerator("Type");
    QMetaEnum metaEnum = mo.enumerator(index);
    for (int i = 0; i < metaEnum.keyCount(); ++i) {
        CorpusObject::Type type = static_cast<CorpusObject::Type>(metaEnum.value(i));
        MetadataStructureSection *mySection;
        foreach (MetadataStructureSection *otherSection, otherStructure->sections(type)) {
            mySection = d->metadataStructure->section(type, otherSection->ID());
            if (mySection) {
                // Copy over name and description, only if this structure does not already define them
                if (mySection->name().isEmpty())
                    mySection->setName(otherSection->name());
                if (mySection->description().isEmpty())
                    mySection->setDescription(otherSection->description());
                // Have section in common, check attributes.
                foreach (MetadataStructureAttribute *otherAttribute, otherSection->attributes()) {
                    MetadataStructureAttribute *myAttribute = mySection->attribute(otherAttribute->ID());
                    if (!myAttribute) {
                        myAttribute = otherAttribute->clone();
                        if (d->datastoreMetadata->createMetadataAttribute(type, myAttribute)) {
                            mySection->addAttribute(myAttribute);
                        } else {
                            errors.emplace_back(QString("Error adding attribute: ").arg(myAttribute->ID()));
                            delete myAttribute;
                        }
                    }
                }
            }
            else {
                // Copy Section from other
                mySection = new MetadataStructureSection(otherSection->ID(), otherSection->name(), otherSection->description());
                d->metadataStructure->addSection(type, mySection);
                foreach (MetadataStructureAttribute *otherAttribute, otherSection->attributes()) {
                    MetadataStructureAttribute *myAttribute = otherAttribute->clone();
                    if (d->datastoreMetadata->createMetadataAttribute(type, myAttribute)) {
                        mySection->addAttribute(myAttribute);
                    } else {
                        errors.emplace_back(QString("Error adding attribute: ").arg(myAttribute->ID()));
                        delete myAttribute;
                    }
                }
            }
        }
    }
}

void CorpusRepository::importAnnotationStructure(AnnotationStructure *otherStructure)
{
    if (!d->datastoreAnnotations) return;
    if (!d->annotationStructure) return;
    AnnotationStructureLevel *myLevel;
    foreach (AnnotationStructureLevel *otherLevel, otherStructure->levels()) {
        myLevel = d->annotationStructure->level(otherLevel->ID());
        if (myLevel) {
            // Copy over name and description, only if this structure does not already define them
            if (myLevel->name().isEmpty())
                myLevel->setName(otherLevel->name());
            if (myLevel->description().isEmpty())
                myLevel->setDescription(otherLevel->description());
            // Have level in common, check attributes.
            foreach (AnnotationStructureAttribute *otherAttribute, otherLevel->attributes()) {
                AnnotationStructureAttribute *myAttribute = myLevel->attribute(otherAttribute->ID());
                if (!myAttribute) {
                    myAttribute = new AnnotationStructureAttribute(otherAttribute);
                    if (d->datastoreAnnotations->createAnnotationAttribute(myLevel->ID(), myAttribute))
                        myLevel->addAttribute(myAttribute);
                    else delete myAttribute;
                }
            }
        }
        else {
            // Copy level from other
            myLevel = new AnnotationStructureLevel(otherLevel->ID(), otherLevel->levelType(), otherLevel->name(),
                                                   otherLevel->description(), otherLevel->parentLevelID(),
                                                   otherLevel->datatype(), otherLevel->itemOrder(),
                                                   otherLevel->indexed(), otherLevel->nameValueList());
            if (d->datastoreAnnotations->createAnnotationLevel(myLevel)) {
                d->annotationStructure->addLevel(myLevel);
                foreach (AnnotationStructureAttribute *otherAttribute, otherLevel->attributes()) {
                    AnnotationStructureAttribute *myAttribute = new AnnotationStructureAttribute(otherAttribute);
                    if (d->datastoreAnnotations->createAnnotationAttribute(myLevel->ID(), myAttribute))
                        myLevel->addAttribute(myAttribute);
                    else delete myAttribute;
                }
            }
            else delete myLevel;
        }
    }
}

// ==============================================================================================================================
// Error handling and logging
// ==============================================================================================================================
QString CorpusRepository::lastError() const
{
    return d->lastError;
}

void CorpusRepository::setLastError(const QString &errorMessage)
{
    d->lastError = errorMessage;
    sendLogMessage("ERROR", errorMessage);
}

void CorpusRepository::clearLastError()
{
    d->lastError.clear();
}

void CorpusRepository::sendLogMessage(const QString &category, const QString &message)
{
    emit logMessage(category, message);
}

PRAALINE_CORE_END_NAMESPACE
