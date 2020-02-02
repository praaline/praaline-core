/*
    Praaline - Annotation module
    Copyright (c) 2011-2016 George Christodoulides

    This program or module is free software: you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation, either version 3 of
    the License, or (at your option) any later version. It is provided
    for educational purposes and is distributed in the hope that it will
    be useful, but WITHOUT ANY WARRANTY; without even the implied
    warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See
    the GNU General Public License for more details.
*/

#include "PraalineCore/Annotation/AnnotationElement.h"
#include "PraalineCore/Annotation/Relation.h"

PRAALINE_CORE_BEGIN_NAMESPACE

Relation::Relation()
{
}

Relation::Relation(int indexFrom, int indexTo, const QString &text, const QHash<QString, QVariant> &attributes) :
    AnnotationElement(text, attributes), m_indexFrom(indexFrom), m_indexTo(indexTo)
{
}

Relation::Relation(const Relation &copy) :
    AnnotationElement(copy.m_text, copy.m_attributes), m_indexFrom(copy.m_indexFrom), m_indexTo(copy.m_indexTo)
{
}

Relation::~Relation()
{
}

Relation *Relation::clone()
{
    return new Relation(m_indexFrom, m_indexTo, m_text, m_attributes);
}

Relation *Relation::cloneWithoutAttributes()
{
    return new Relation(m_indexFrom, m_indexTo, m_text);
}

QVariant Relation::attribute(const QString &name) const
{
    if (name == "indexFrom") return indexFrom();
    if (name == "indexTo") return indexTo();
    return AnnotationElement::attribute(name);
}

void Relation::setAttribute(const QString &name, QVariant value) {
    if ((name == "indexFrom") || (name == "indexTo")) return;
    AnnotationElement::setAttribute(name, value);
}

int Relation::compare(const Relation &other) const
{
    if (other.m_indexFrom < m_indexFrom) return 1;
    if (other.m_indexFrom > m_indexFrom) return -1;
    if (other.m_indexTo < m_indexTo) return 1;
    if (other.m_indexTo > m_indexTo) return -1;
    return other.m_text.compare(m_text);
}

PRAALINE_CORE_END_NAMESPACE

