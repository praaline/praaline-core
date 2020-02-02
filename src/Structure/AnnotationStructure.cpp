#include <QObject>
#include <QString>
#include <QList>
#include "PraalineCore/Structure/AnnotationStructure.h"

PRAALINE_CORE_BEGIN_NAMESPACE

AnnotationStructure::AnnotationStructure(QObject *parent) :
    QObject(parent)
{
}

AnnotationStructure::~AnnotationStructure()
{
    // Levels are QObjects, they are deleted as children of this QObject.
}

// ==========================================================================================================
// Data
// ==========================================================================================================

QString AnnotationStructure::ID() const
{
    return m_ID;
}

void AnnotationStructure::setID(const QString &ID)
{
    m_ID = ID;
}

// ==========================================================================================================
// Annotation levels
// ==========================================================================================================

AnnotationStructureLevel *AnnotationStructure::level(int index) const
{
    return m_levels.value(index);
}

AnnotationStructureLevel *AnnotationStructure::level(const QString &ID) const
{
    foreach (AnnotationStructureLevel *level, m_levels) {
        if ((level) && (level->ID() == ID))
            return level;
    }
    return nullptr;
}

int AnnotationStructure::levelIndexByID(const QString &ID) const
{
    for (int i = 0; i < m_levels.count(); i++ ) {
        if ((m_levels[i]) && (m_levels[i]->ID() == ID)) return i;
    }
    return -1;
}

int AnnotationStructure::levelsCount() const
{
    return m_levels.count();
}

bool AnnotationStructure::hasLevel(const QString &ID) const
{
    return (levelIndexByID(ID) != -1);
}

bool AnnotationStructure::hasLevels() const
{
    return !m_levels.isEmpty();
}

QStringList AnnotationStructure::levelIDs() const
{
    QStringList ret;
    foreach (AnnotationStructureLevel *level, m_levels)
        if (level) ret << level->ID();
    return ret;
}

QList<AnnotationStructureLevel *> AnnotationStructure::levels() const
{
    return m_levels;
}

bool AnnotationStructure::insertLevel(int index, AnnotationStructureLevel *level)
{
    if (!level) return false;
    if (hasLevel(level->ID())) return false;
    level->setParent(this);
    m_levels.insert(index, level);
    emit levelAdded(this, level);
    return true;
}

bool AnnotationStructure::addLevel(AnnotationStructureLevel *level)
{
    if (!level) return false;
    if (hasLevel(level->ID())) return false;
    level->setParent(this);
    m_levels << level;
    emit levelAdded(this, level);
    return true;
}

void AnnotationStructure::swapLevels(int oldIndex, int newIndex)
{
    m_levels.swapItemsAt(oldIndex, newIndex);
}

void AnnotationStructure::removeLevelAt(int i)
{
    if ((i < 0) || (i >= m_levels.count())) return;
    AnnotationStructureLevel *level = m_levels.at(i);
    m_levels.removeAt(i);
    if (level) {
        QString levelID = level->ID();
        delete level;
        emit levelDeleted(this, levelID);
    }
}

void AnnotationStructure::removeLevelByID(const QString &ID)
{
    int i = levelIndexByID(ID);
    if (i != -1)
        removeLevelAt(i);
}

void AnnotationStructure::clear()
{
    for (int i = levelsCount() - 1; i >= 0; i--) {
        removeLevelAt(levelsCount() - 1);
    }
}

PRAALINE_CORE_END_NAMESPACE
