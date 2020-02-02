#ifndef ANNOTATIONELEMENT_H
#define ANNOTATIONELEMENT_H

/*
    Praaline - Core module - Annotation
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

#include <QString>
#include <QVariant>
#include <QHash>
#include "PraalineCore/PraalineCore_Global.h"
#include "PraalineCore/Base/RealTime.h"
#include "PraalineCore/Base/ISaveable.h"

PRAALINE_CORE_BEGIN_NAMESPACE

/**
 * @brief The AnnotationElement class
 */

class PRAALINE_CORE_SHARED_EXPORT AnnotationElement : public ISaveable
{
    friend class AnnotationTier;

public:
    /**
     * @brief AnnotationElement
     */
    AnnotationElement();
    /**
     * @brief AnnotationElement
     * @param text
     */
    explicit AnnotationElement(const QString &text);
    /**
     * @brief AnnotationElement
     * @param text
     * @param attributes
     */
    AnnotationElement(const QString &text, const QHash<QString, QVariant> &attributes);
    /**
     * @brief AnnotationElement
     * @param other
     */
    AnnotationElement(const AnnotationElement &other);
    /**
     * @brief ~AnnotationElement
     */
    virtual ~AnnotationElement() override;
    // Notes: Requirements for QVariant are a public default constructor, a public copy constructor, and a public
    // destructor.
    // All constructors set isNew and isDirty to true. If the object is retrieved from the database, the datastore
    // will set its state to Clean.

    /**
     * @brief The ElementType enum
     */
    enum ElementType {
        Type_Element,
        Type_Point,
        Type_Interval,
        Type_Sequence,
        Type_Relation
    };

    /**
     * @brief elementType
     * @return
     */
    inline virtual ElementType elementType() const {
        return AnnotationElement::Type_Element;
    }

    /**
     * @brief text
     * @return
     */
    inline virtual QString text() const {
        return m_text;
    }

    /**
     * @brief setText
     * @param text
     */
    inline virtual void setText(const QString &text) {
        if (m_text != text) {
            m_text = text;
            m_isDirty = true;
        }
    }

    /**
     * @brief appendText
     * @param appendedText
     */
    inline virtual void appendText(const QString &appendedText) {
        m_text.append(appendedText);
        m_isDirty = true;
    }

    /**
     * @brief replaceText
     * @param before
     * @param after
     * @param cs
     */
    inline virtual void replaceText(const QString &before, const QString &after, Qt::CaseSensitivity cs = Qt::CaseSensitive) {
        m_text.replace(before, after, cs);
        m_isDirty = true;
    }

    /**
     * @brief replaceAttributeText
     * @param attributeID
     * @param before
     * @param after
     * @param cs
     */
    inline virtual void replaceAttributeText(const QString &attributeID, const QString &before, const QString &after, Qt::CaseSensitivity cs = Qt::CaseSensitive) {
        if (!m_attributes.contains(attributeID)) return;
        m_attributes[attributeID] = m_attributes[attributeID].toString().replace(before, after, cs);
        m_isDirty = true;
    }

    /**
     * @brief attribute
     * @param name
     * @return
     */
    inline virtual QVariant attribute(const QString &name) const {
        if (name == "text") return text();
        return m_attributes.value(name, QVariant());
    }

    /**
     * @brief setAttribute
     * @param name
     * @param value
     */
    inline virtual void setAttribute(const QString &name, QVariant value) {
        if (name == "text")
            setText(value.toString());
        else {
            m_attributes.insert(name, value);
            m_isDirty = true;
        }
    }

    /**
     * @brief removeAttribute
     * @param name
     */
    inline virtual void removeAttribute(const QString &name) {
        m_attributes.remove(name);
    }

    /**
     * @brief clearAttributes
     */
    inline virtual void clearAttributes() {
        m_attributes.clear();
    }

    /**
     * @brief attributes
     * @return
     */
    inline virtual QHash<QString, QVariant> attributes() const {
        return m_attributes;
    }

    /**
     * @brief attributeNames
     * @return
     */
    inline virtual QList<QString> attributeNames() const {
        return m_attributes.keys();
    }

protected:
    QString m_text;
    QVariantHash m_attributes;
};

PRAALINE_CORE_END_NAMESPACE

Q_DECLARE_METATYPE(PRAALINE_CORE_NAMESPACE::AnnotationElement)

#endif // ANNOTATIONELEMENT_H
