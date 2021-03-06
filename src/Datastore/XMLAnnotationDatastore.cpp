#include <QString>
#include <QMap>

#include "PraalineCore/Annotation/IntervalTier.h"
#include "PraalineCore/Structure/AnnotationStructure.h"
#include "PraalineCore/Datastore/CorpusRepository.h"
#include "PraalineCore/Datastore/DatastoreInfo.h"

#include "Datastore/XMLAnnotationDatastore.h"

PRAALINE_CORE_BEGIN_NAMESPACE

XMLAnnotationDatastore::XMLAnnotationDatastore(AnnotationStructure *structure, CorpusRepository *repository, QObject *parent) :
    AnnotationDatastore(repository, parent), m_structure(structure)
{
}

XMLAnnotationDatastore::~XMLAnnotationDatastore()
{
}

// ==========================================================================================================================
// Datastore
// ==========================================================================================================================
bool XMLAnnotationDatastore::createDatastore(const DatastoreInfo &info)
{
    Q_UNUSED(info)
    return false;
}

bool XMLAnnotationDatastore::openDatastore(const DatastoreInfo &info)
{
    Q_UNUSED(info)
    return false;
}

bool XMLAnnotationDatastore::closeDatastore()
{
    return false;
}

// ==========================================================================================================================
// Annotation Structure
// ==========================================================================================================================
bool XMLAnnotationDatastore::loadAnnotationStructure()
{
    return false;
}

bool XMLAnnotationDatastore::saveAnnotationStructure()
{
    return false;
}

bool XMLAnnotationDatastore::createAnnotationLevel(AnnotationStructureLevel *newLevel)
{
    Q_UNUSED(newLevel)
    return false;
}

bool XMLAnnotationDatastore::renameAnnotationLevel(const QString &levelID, const QString &newLevelID)
{
    Q_UNUSED(levelID)
    Q_UNUSED(newLevelID)
    return false;
}

bool XMLAnnotationDatastore::deleteAnnotationLevel(const QString &levelID)
{
    Q_UNUSED(levelID)
    return false;
}

bool XMLAnnotationDatastore::createAnnotationAttribute(const QString &levelID, AnnotationStructureAttribute *newAttribute)
{
    Q_UNUSED(levelID)
    Q_UNUSED(newAttribute)
    return false;
}

bool XMLAnnotationDatastore::renameAnnotationAttribute(const QString &levelID, const QString &attributeID, const QString &newAttributeID)
{
    Q_UNUSED(levelID)
    Q_UNUSED(attributeID)
    Q_UNUSED(newAttributeID)
    return false;
}

bool XMLAnnotationDatastore::deleteAnnotationAttribute(const QString &levelID, const QString &attributeID)
{
    Q_UNUSED(levelID)
    Q_UNUSED(attributeID)
    return false;
}

bool XMLAnnotationDatastore::retypeAnnotationAttribute(const QString &levelID, const QString &attributeID, const DataType &newDatatype)
{
    Q_UNUSED(levelID)
    Q_UNUSED(attributeID)
    Q_UNUSED(newDatatype)
    return false;
}

// ==========================================================================================================================
// Name-value lists
// ==========================================================================================================================
NameValueList *XMLAnnotationDatastore::getNameValueList(const QString &listID)
{
    Q_UNUSED(listID)
    return nullptr;
}

QStringList XMLAnnotationDatastore::getAllNameValueListIDs()
{
    QStringList ret;
    return ret;
}

QMap<QString, NameValueList *> XMLAnnotationDatastore::getAllNameValueLists()
{
    QMap<QString, NameValueList *> ret;
    return ret;
}

bool XMLAnnotationDatastore::createNameValueList(NameValueList *list)
{
    Q_UNUSED(list)
    return false;
}

bool XMLAnnotationDatastore::updateNameValueList(NameValueList *list)
{
    Q_UNUSED(list)
    return false;
}

bool XMLAnnotationDatastore::deleteNameValueList(const QString &listID)
{
    Q_UNUSED(listID)
    return false;
}

// ==========================================================================================================================
// Annotation Tiers
// ==========================================================================================================================
AnnotationTier *XMLAnnotationDatastore::getTier(const QString &annotationID, const QString &speakerID,
                                                const QString &levelID, const QStringList &attributeIDs)
{
    Q_UNUSED(annotationID)
    Q_UNUSED(speakerID)
    Q_UNUSED(levelID)
    Q_UNUSED(attributeIDs)
    return nullptr;
}

AnnotationTierGroup *XMLAnnotationDatastore::getTiers(const QString &annotationID, const QString &speakerID, const QStringList &levelIDs)
{
    Q_UNUSED(annotationID)
    Q_UNUSED(speakerID)
    Q_UNUSED(levelIDs)
    return nullptr;
}

QMap<QString, AnnotationTierGroup *> XMLAnnotationDatastore::getTiersAllSpeakers(const QString &annotationID, const QStringList &levelIDs)
{
    Q_UNUSED(annotationID)
    Q_UNUSED(levelIDs)
    QMap<QString, AnnotationTierGroup *> ret;
    return ret;
}

bool XMLAnnotationDatastore::saveTier(const QString &annotationID, const QString &speakerID, AnnotationTier *tier)
{
    Q_UNUSED(annotationID)
    Q_UNUSED(speakerID)
    Q_UNUSED(tier)
    return false;
}

bool XMLAnnotationDatastore::saveTiers(const QString &annotationID, const QString &speakerID, AnnotationTierGroup *tiers)
{
    Q_UNUSED(annotationID)
    Q_UNUSED(speakerID)
    Q_UNUSED(tiers)
    return false;
}

bool XMLAnnotationDatastore::saveTiersAllSpeakers(const QString &annotationID, QMap<QString, AnnotationTierGroup *> &tiersAllSpeakers)
{
    Q_UNUSED(annotationID)
    Q_UNUSED(tiersAllSpeakers)
    return false;
}

bool XMLAnnotationDatastore::deleteTier(const QString &annotationID, const QString &speakerID, const QString &levelID)
{
    Q_UNUSED(annotationID)
    Q_UNUSED(speakerID)
    Q_UNUSED(levelID)
    return false;
}

bool XMLAnnotationDatastore::deleteTiers(const QString &annotationID, const QString &speakerID, const QStringList &levelIDs)
{
    Q_UNUSED(annotationID)
    Q_UNUSED(speakerID)
    Q_UNUSED(levelIDs)
    return false;
}

bool XMLAnnotationDatastore::deleteAllTiersAllSpeakers(const QString &annotationID)
{
    Q_UNUSED(annotationID)
    return false;
}

// ==========================================================================================================================
// Annotation Elements
// ==========================================================================================================================
QList<AnnotationElement *> XMLAnnotationDatastore::getAnnotationElements(const Selection &selection)
{
    Q_UNUSED(selection)
    QList<AnnotationElement *> ret;
    return ret;
}

QList<Point *> XMLAnnotationDatastore::getPoints(const Selection &selection)
{
    Q_UNUSED(selection)
    QList<Point *> ret;
    return ret;
}

QList<Interval *> XMLAnnotationDatastore::getIntervals(const Selection &selection)
{
    Q_UNUSED(selection)
    QList<Interval *> ret;
    return ret;
}

QList<Sequence *> XMLAnnotationDatastore::getSequences(const Selection &selection)
{
    Q_UNUSED(selection)
    QList<Sequence *> ret;
    return ret;
}

bool XMLAnnotationDatastore::saveAnnotationElements(const QList<AnnotationElement *> &elements, const QString &levelID,
                                                    const QStringList &attributeIDs)
{
    Q_UNUSED(elements)
    Q_UNUSED(levelID)
    Q_UNUSED(attributeIDs)
    return false;
}

// ==========================================================================================================================
// Speakers and Timeline
// ==========================================================================================================================
QStringList XMLAnnotationDatastore::getSpeakersInLevel(const QString &annotationID, const QString &levelID)
{
    Q_UNUSED(annotationID)
    Q_UNUSED(levelID)
    QStringList ret;
    return ret;
}

QStringList XMLAnnotationDatastore::getSpeakersActiveInLevel(const QString &annotationID, const QString &levelID)
{
    Q_UNUSED(annotationID)
    Q_UNUSED(levelID)
    QStringList ret;
    return ret;
}

QStringList XMLAnnotationDatastore::getSpeakersInAnnotation(const QString &annotationID)
{
    Q_UNUSED(annotationID)
    QStringList ret;
    return ret;
}

QStringList XMLAnnotationDatastore::getSpeakersActiveInAnnotation(const QString &annotationID)
{
    Q_UNUSED(annotationID)
    QStringList ret;
    return ret;
}

IntervalTier *XMLAnnotationDatastore::getSpeakerTimeline(const QString &communicationID,const QString &annotationID,
                                                         const QString &levelID, bool detailed)
{
    Q_UNUSED(communicationID)
    Q_UNUSED(annotationID)
    Q_UNUSED(levelID)
    Q_UNUSED(detailed)
    return nullptr;
}

// ==========================================================================================================================
// Queries
// ==========================================================================================================================
QList<QueryOccurrencePointer *> XMLAnnotationDatastore::runQuery(QueryDefinition *qdef)
{
    Q_UNUSED(qdef)
    QList<QueryOccurrencePointer *> ret;
    return ret;
}

QueryOccurrence *XMLAnnotationDatastore::getOccurrence(QueryOccurrencePointer *pointer, QueryDefinition *qdef,
                                                       int lengthContextLeft, int lengthContextRight)
{
    Q_UNUSED(pointer)
    Q_UNUSED(qdef)
    Q_UNUSED(lengthContextLeft)
    Q_UNUSED(lengthContextRight)
    return nullptr;
}

bool XMLAnnotationDatastore::updateAnnotationsFromQueryOccurrences(const QList<QueryOccurrence *> &occurrences)
{
    Q_UNUSED(occurrences)
    return false;
}

// ==========================================================================================================================
// Batch Processing
// ==========================================================================================================================
QList<QPair<QList<QVariant>, long> > XMLAnnotationDatastore::getDistinctLabels(const QString &levelID, const QStringList &attributeIDs)
{
    Q_UNUSED(levelID)
    Q_UNUSED(attributeIDs)
    QList<QPair<QList<QVariant>, long> > ret;
    return ret;
}

bool XMLAnnotationDatastore::batchUpdate(const QString &levelID, const QString &attributeID, const QVariant &newValue,
                                         const QList<QPair<QString, QVariant> > &criteria)
{
    Q_UNUSED(levelID)
    Q_UNUSED(attributeID)
    Q_UNUSED(newValue)
    Q_UNUSED(criteria)
    return false;
}

// ==========================================================================================================================
// Statistics
// ==========================================================================================================================
QList<QPair<QList<QVariant>, long long> > XMLAnnotationDatastore::countItems(const QString &levelID, const QStringList &groupByAttributeIDs,
                                                                             bool excludeNULL, QStringList excludeValues)
{
    Q_UNUSED(levelID)
    Q_UNUSED(groupByAttributeIDs)
    Q_UNUSED(excludeNULL)
    Q_UNUSED(excludeValues)
    QList<QPair<QList<QVariant>, long long> > ret;
    return ret;
}

PRAALINE_CORE_END_NAMESPACE
