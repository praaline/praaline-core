#ifndef CORPUSOBJECT_H
#define CORPUSOBJECT_H

/*
    Praaline - Core module - Corpus metadata
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
#include <QVariant>
#include "PraalineCore/PraalineCore_Global.h"
#include "PraalineCore/Base/ISaveable.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class CorpusRepository;

class PRAALINE_CORE_SHARED_EXPORT CorpusObject : public QObject, public ISaveable
{
    Q_OBJECT
    Q_PROPERTY(QString ID READ ID WRITE setID)
    Q_PROPERTY(QString originalID READ originalID)
    Q_PROPERTY(QString corpusID READ corpusID WRITE setCorpusID)
    Q_PROPERTY(Type type READ type)

public:
    enum Type {
        Type_Corpus,
        Type_Communication,
        Type_Speaker,
        Type_Recording,
        Type_Annotation,
        Type_Participation,
        Type_Bookmark,
        Type_SpeakerRelation,
        Type_Undefined
    };
    Q_ENUM(Type)

    // User-friendly and translated names
    static QString typeToFriendlyString(CorpusObject::Type type);
    // String types for XML and JSON
    static QString typeToString(CorpusObject::Type type);
    static CorpusObject::Type stringToType(const QString &str);

    explicit CorpusObject(CorpusRepository *repository = nullptr, QObject *parent = nullptr);
    explicit CorpusObject(const QString &ID, CorpusRepository *repository = nullptr, QObject *parent = nullptr);
    virtual ~CorpusObject() {}

    virtual QString ID() const { return m_ID; }
    virtual void setID(const QString &ID);
    virtual QString originalID() const { return m_originalID; }

    virtual QString corpusID() const { return m_corpusID; }
    virtual void setCorpusID(const QString &corpusID);

    // Subclasses (different types of corpus objects) must override this
    virtual CorpusObject::Type type() const = 0;
    virtual bool save() = 0;

    // Get/set properties using QString names
    QVariant property(const QString &name) const;
    bool setProperty(const QString &name, const QVariant &value);

    CorpusRepository *repository() const { return m_repository; }

signals:
    void changedID(const QString &oldID, const QString &newID);

protected:
    QString m_ID;
    QString m_originalID;
    QString m_corpusID;
    CorpusRepository *m_repository;

    void copyPropertiesFrom(CorpusObject *other);

    // Monitor dynamic property changes
    bool eventFilter(QObject *obj, QEvent *event);

private:
    friend class CorpusDatastore;
    Q_DISABLE_COPY(CorpusObject)
};

PRAALINE_CORE_END_NAMESPACE

#endif // CORPUSOBJECT_H
