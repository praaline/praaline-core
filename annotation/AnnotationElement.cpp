#include "AnnotationElement.h"

PRAALINE_CORE_BEGIN_NAMESPACE

AnnotationElement::AnnotationElement()
{
    m_isNew = true;
    m_isDirty = true;
}

AnnotationElement::AnnotationElement(const QString &text) :
    m_text(text)
{
    m_isNew = true;
    m_isDirty = true;
}

AnnotationElement::AnnotationElement(const QString &text, const QHash<QString, QVariant> &attributes) :
    m_text(text), m_attributes(attributes)
{
    m_isNew = true;
    m_isDirty = true;
}

AnnotationElement::AnnotationElement(const AnnotationElement &other) :
    m_text(other.m_text), m_attributes(other.m_attributes)
{
    m_isNew = true;
    m_isDirty = true;
}

AnnotationElement::~AnnotationElement()
{
}

PRAALINE_CORE_END_NAMESPACE
