#include <QString>
#include "PraalineCore/Structure/AnnotationStructure.h"
#include "PraalineCore/Serialisers/Base/SerialiserAnnotationStructure.h"

PRAALINE_CORE_BEGIN_NAMESPACE

SerialiserAnnotationStructure::SerialiserAnnotationStructure()
{
}

SerialiserAnnotationStructure::~SerialiserAnnotationStructure()
{
}

QString SerialiserAnnotationStructure::convertLevelTypeToString(AnnotationStructureLevel::LevelType levelType)
{
    QString ret("independentintervals");
    switch(levelType) {
    case AnnotationStructureLevel::IndependentPointsLevel:      ret = "independentpoints";    break;
    case AnnotationStructureLevel::IndependentIntervalsLevel:   ret = "independentintervals"; break;
    case AnnotationStructureLevel::GroupingLevel:               ret = "grouping";             break;
    case AnnotationStructureLevel::SequencesLevel:              ret = "sequences";            break;
    case AnnotationStructureLevel::TreeLevel:                   ret = "tree";                 break;
    case AnnotationStructureLevel::RelationsLevel:              ret = "relations";            break;
    }
    return ret;
}

AnnotationStructureLevel::LevelType SerialiserAnnotationStructure::convertStringToLevelType(QString str)
{
    if (str == "independentpoints")     return AnnotationStructureLevel::IndependentPointsLevel;
    if (str == "independentintervals")  return AnnotationStructureLevel::IndependentIntervalsLevel;
    if (str == "grouping")              return AnnotationStructureLevel::GroupingLevel;
    if (str == "sequences")             return AnnotationStructureLevel::SequencesLevel;
    if (str == "tree")                  return AnnotationStructureLevel::TreeLevel;
    if (str == "relations")             return AnnotationStructureLevel::RelationsLevel;
    return AnnotationStructureLevel::IndependentIntervalsLevel;
}

PRAALINE_CORE_END_NAMESPACE
