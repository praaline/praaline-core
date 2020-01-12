#include <QString>
#include <QList>
#include <QHash>

#include "annotation/AnnotationTier.h"

PRAALINE_CORE_BEGIN_NAMESPACE

AnnotationTier::AnnotationTier(const QString &name, QObject *parent) :
    QObject (parent), m_name(name)
{
}

AnnotationTier::~AnnotationTier()
{
}

QString AnnotationTier::name() const
{
    return m_name;
}

void AnnotationTier::setName(const QString &name)
{
    if (m_name != name) {
        m_name = name;
        emit nameChanged();
    }
}

RealTime AnnotationTier::tMin() const
{
    return m_tMin;
}

RealTime AnnotationTier::tMax() const
{
    return m_tMax;
}

RealTime AnnotationTier::duration() const
{
    return m_tMax - m_tMin;
}

PRAALINE_CORE_END_NAMESPACE
