#include <QObject>
#include <QVariant>
#include <QDynamicPropertyChangeEvent>

#include "PraalineCore/Base/ISaveable.h"
#include "PraalineCore/Datastore/CorpusRepository.h"
#include "PraalineCore/Corpus/CorpusObject.h"

PRAALINE_CORE_BEGIN_NAMESPACE

CorpusObject::CorpusObject(CorpusRepository *repository, QObject *parent) :
    QObject(parent), m_ID(QString()), m_originalID(QString()), m_repository(repository)
{
    m_isDirty = true;
    m_isNew = true;
}

CorpusObject::CorpusObject(const QString &ID, CorpusRepository *repository, QObject *parent) :
    QObject(parent), m_ID(ID), m_originalID(ID), m_repository(repository)
{
    m_isDirty = true;
    m_isNew = true;
}

void CorpusObject::setID(const QString &ID)
{
    if (m_ID != ID) {
        QString oldID = m_ID;
        m_ID = ID;
        m_isDirty = true;
        emit changedID(oldID, m_ID);
    }
}

void CorpusObject::setCorpusID(const QString &corpusID)
{
    if (m_corpusID != corpusID) {
        m_corpusID = corpusID;
        m_isDirty = true;
    }
}

QVariant CorpusObject::property(const QString &name) const
{
    return QObject::property(name.toLatin1().constData());
}

bool CorpusObject::setProperty(const QString &name, const QVariant &value)
{
    m_isDirty = true;
    return QObject::setProperty(name.toLatin1().constData(), value);
}

bool CorpusObject::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::DynamicPropertyChange) {
        m_isDirty = true;
    }
    return QObject::eventFilter(obj, event);
}

void CorpusObject::copyPropertiesFrom(CorpusObject *other)
{
    if (!other) return;
    foreach (const QByteArray &propertyName, other->dynamicPropertyNames())
        setProperty(propertyName.constData(), other->property(propertyName.constData()));
    m_isDirty = true;
}

// static
QString CorpusObject::typeToFriendlyString(CorpusObject::Type type)
{
    QString ret;
    switch (type) {
    case CorpusObject::Type_Corpus:          ret = tr("Corpus");            break;
    case CorpusObject::Type_Communication:   ret = tr("Communication");     break;
    case CorpusObject::Type_Speaker:         ret = tr("Speaker");           break;
    case CorpusObject::Type_Recording:       ret = tr("Recording");         break;
    case CorpusObject::Type_Annotation:      ret = tr("Annotation");        break;
    case CorpusObject::Type_Participation:   ret = tr("Participation");     break;
    case CorpusObject::Type_SpeakerRelation: ret = tr("Speaker Relation");  break;
    case CorpusObject::Type_Bookmark:        ret = tr("Bookmark");          break;
    case CorpusObject::Type_Undefined:       ret = tr("Corpus Item");       break;
    }
    return ret;
}

// static
QString CorpusObject::typeToString(CorpusObject::Type type)
{
    QString ret("CorpusObject");
    switch (type) {
    case CorpusObject::Type_Corpus:          ret = tr("Corpus");            break;
    case CorpusObject::Type_Communication:   ret = tr("Communication");     break;
    case CorpusObject::Type_Speaker:         ret = tr("Speaker");           break;
    case CorpusObject::Type_Recording:       ret = tr("Recording");         break;
    case CorpusObject::Type_Annotation:      ret = tr("Annotation");        break;
    case CorpusObject::Type_Participation:   ret = tr("Participation");     break;
    case CorpusObject::Type_SpeakerRelation: ret = tr("SpeakerRelation");   break;
    case CorpusObject::Type_Bookmark:        ret = tr("Bookmark");          break;
    case CorpusObject::Type_Undefined:       ret = tr("CorpusObject");      break;
    }
    return ret;
}

// static
CorpusObject::Type CorpusObject::stringToType(const QString &str)
{
    if      (str == "Corpus")           return CorpusObject::Type_Corpus;
    else if (str == "Communication")    return CorpusObject::Type_Communication;
    else if (str == "Speaker")          return CorpusObject::Type_Speaker;
    else if (str == "Recording")        return CorpusObject::Type_Recording;
    else if (str == "Annotation")       return CorpusObject::Type_Annotation;
    else if (str == "Participation")    return CorpusObject::Type_Participation;
    else if (str == "SpeakerRelation")  return CorpusObject::Type_SpeakerRelation;
    else if (str == "Bookmark")         return CorpusObject::Type_Bookmark;
    return CorpusObject::Type_Undefined;
}

PRAALINE_CORE_END_NAMESPACE
