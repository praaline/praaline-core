#include <QObject>
#include <QString>
#include <QList>
#include <QHash>
#include <QMetaEnum>
#include "MetadataStructure.h"

PRAALINE_CORE_BEGIN_NAMESPACE

// private
void MetadataStructure::createDefaultSection(CorpusObject::Type what)
{
    if (what == CorpusObject::Type_Corpus) {
        m_sections[CorpusObject::Type_Corpus].append(
                    new MetadataStructureSection("corpus", tr("Corpus"), tr("Corpus Metadata"), 0, this));
    } else if (what == CorpusObject::Type_Communication) {
        m_sections[CorpusObject::Type_Communication].append(
                    new MetadataStructureSection("communication", tr("Communication"), tr("Communication Metadata"), 0, this));
    } else if (what == CorpusObject::Type_Speaker) {
        m_sections[CorpusObject::Type_Speaker].append(
                    new MetadataStructureSection("speaker", tr("Speaker"), tr("Speaker Metadata"), 0, this));
    } else if (what == CorpusObject::Type_Recording) {
        m_sections[CorpusObject::Type_Recording].append(
                    new MetadataStructureSection("recording", tr("Recording"), tr("Recording Metadata"), 0, this));
    } else if (what == CorpusObject::Type_Annotation) {
        m_sections[CorpusObject::Type_Annotation].append(
                    new MetadataStructureSection("annotation", tr("Annotation"), tr("Annotation Metadata"), 0, this));
    } else if (what == CorpusObject::Type_Participation) {
        m_sections[CorpusObject::Type_Participation].append(
                    new MetadataStructureSection("participation", tr("Participation"), tr("Participation Metadata"), 0, this));
    }
}

MetadataStructure::MetadataStructure(QObject *parent) :
    QObject(parent)
{
    // There is always a default metadata section for each corpus object type
    createDefaultSection(CorpusObject::Type_Corpus);
    createDefaultSection(CorpusObject::Type_Communication);
    createDefaultSection(CorpusObject::Type_Speaker);
    createDefaultSection(CorpusObject::Type_Recording);
    createDefaultSection(CorpusObject::Type_Annotation);
    createDefaultSection(CorpusObject::Type_Participation);
}

MetadataStructure::~MetadataStructure()
{
    // Sections are QObjects, they will be deleted when their parent (this) is deleted.
}

// ==========================================================================================================
// Metadata structure sections
// ==========================================================================================================

MetadataStructureSection *MetadataStructure::section(CorpusObject::Type what, int index) const
{
    if (!m_sections.contains(what)) return nullptr;
    return m_sections[what].value(index);
}

MetadataStructureSection *MetadataStructure::section(CorpusObject::Type what, const QString &ID) const
{
    if (!m_sections.contains(what)) return nullptr;
    foreach (MetadataStructureSection *section, m_sections[what]) {
        if ((section) && section->ID() == ID)
            return section;
    }
    return nullptr;
}

int MetadataStructure::sectionIndexByID(CorpusObject::Type what, const QString &ID) const
{
    if (!m_sections.contains(what)) return -1;
    for (int i = 0; i < m_sections[what].count(); i++ ) {
        if ((m_sections[what][i]) && (m_sections[what][i]->ID() == ID))
            return i;
    }
    return -1;
}

int MetadataStructure::sectionsCount(CorpusObject::Type what) const
{
    if (!m_sections.contains(what)) return 0;
    return m_sections[what].count();
}

bool MetadataStructure::hasSections(CorpusObject::Type what) const
{
    if (!m_sections.contains(what)) return false;
    return !m_sections[what].isEmpty();
}

bool MetadataStructure::hasSection(CorpusObject::Type what, const QString &ID) const
{
    return (sectionIndexByID(what, ID) != -1);
}

QList<MetadataStructureSection *> MetadataStructure::sections(CorpusObject::Type what) const
{
    return m_sections[what];
}

bool MetadataStructure::replaceDefaultSection(CorpusObject::Type what, MetadataStructureSection *section)
{
    if (!section) return false;
    section->setParent(this);
    MetadataStructureSection *previousDefaultSection = m_sections[what].takeFirst();
    m_sections[what].prepend(section);
    delete previousDefaultSection;
    emit sectionDeleted(this, what, defaultSectionID(what));
    emit sectionAdded(this, what, section);
    return true;
}

bool MetadataStructure::insertSection(CorpusObject::Type what, int index, MetadataStructureSection *section)
{
    if (!section) return false;
    if (section->ID() == defaultSectionID(what)) {
        replaceDefaultSection(what, section);
    }
    if (hasSection(what, section->ID())) return false;
    section->setParent(this);
    if (index == 0) index = 1; // you cannot insert before the default
    m_sections[what].insert(index, section);
    emit sectionAdded(this, what, section);
    return true;
}

bool MetadataStructure::addSection(CorpusObject::Type what, MetadataStructureSection *section)
{
    if (!section) return false;
    if (section->ID() == defaultSectionID(what)) {
        replaceDefaultSection(what, section);
    }
    if (hasSection(what, section->ID())) return false;
    section->setParent(this);
    m_sections[what] << section;
    emit sectionAdded(this, what, section);
    return true;
}

void MetadataStructure::swapSections(CorpusObject::Type what, int oldIndex, int newIndex)
{
    if ((oldIndex == 0) || (newIndex == 0)) return;
    m_sections[what].swapItemsAt(oldIndex, newIndex);
}


void MetadataStructure::removeSectionAt(CorpusObject::Type what, int i)
{
    // cannot remove default section (at index 0)
    if ((i <= 0) || (i >= m_sections[what].count())) return;
    MetadataStructureSection *section = m_sections[what].at(i);
    m_sections[what].removeAt(i);
    if (section) {
        QString sectionID = section->ID();
        delete section;
        emit sectionDeleted(this, what, sectionID);
    }
}

void MetadataStructure::removeSectionByID(CorpusObject::Type what, const QString &ID)
{
    int i = sectionIndexByID(what, ID);
    if ((i != -1) && (i != 0)) {
        removeSectionAt(what, i);
    }
}

void MetadataStructure::clear(CorpusObject::Type what)
{
    // Delete all sections except the default one
    for (int i = sectionsCount(what) - 1; i > 0; i--) {
        removeSectionAt(what, sectionsCount(what) - 1);
    }
    // Clear the default section
    m_sections[what].at(0)->clear();
}

void MetadataStructure::clearAll()
{
    foreach (CorpusObject::Type what, m_sections.keys()) {
        clear(what);
    }
}

// ==========================================================================================================
// Direct access to attributes
// ==========================================================================================================

MetadataStructureAttribute *MetadataStructure::attribute(CorpusObject::Type what, const QString &ID) const
{
    foreach (MetadataStructureSection *section, m_sections[what]) {
        if (!section) continue;
        foreach (MetadataStructureAttribute *attribute, section->attributes())
            if ((attribute) && (attribute->ID() == ID))
                return attribute;
    }
    return nullptr;
}

QList<MetadataStructureAttribute *> MetadataStructure::attributes(CorpusObject::Type what) const
{
    QList<MetadataStructureAttribute *> ret;
    if (!m_sections.contains(what)) return ret;
    foreach (MetadataStructureSection *section, m_sections[what]) {
        if (!section) continue;
        foreach (MetadataStructureAttribute *attribute, section->attributes()) {
            if (attribute) ret << attribute;
        }
    }
    return ret;
}

QStringList MetadataStructure::attributeIDs(CorpusObject::Type what) const
{
    QStringList ret;
    if (!m_sections.contains(what)) return ret;
    foreach (MetadataStructureSection *section, m_sections[what]) {
        if (!section) continue;
        ret << section->attributeIDs();
    }
    return ret;
}

QStringList MetadataStructure::attributeNames(CorpusObject::Type what) const
{
    QStringList ret;
    if (!m_sections.contains(what)) return ret;
    foreach (MetadataStructureSection *section, m_sections[what]) {
        if (!section) continue;
        ret << section->attributeNames();
    }
    return ret;
}

CorpusObject::Type MetadataStructure::corpusObjectTypeOfSection(MetadataStructureSection *section) const
{
    foreach (CorpusObject::Type type, m_sections.keys()) {
        if (m_sections[type].contains(section))
            return type;
    }
    return CorpusObject::Type_Undefined;
}

// ==========================================================================================================
// Defaults
// ==========================================================================================================

// static
QString MetadataStructure::defaultSectionID(CorpusObject::Type type)
{
    if      (type == CorpusObject::Type_Corpus)         return "corpus";
    else if (type == CorpusObject::Type_Communication)  return "communication";
    else if (type == CorpusObject::Type_Speaker)        return "speaker";
    else if (type == CorpusObject::Type_Recording)      return "recording";
    else if (type == CorpusObject::Type_Annotation)     return "annotation";
    else if (type == CorpusObject::Type_Participation)  return "participation";
    return QString();
}

// static
QStringList MetadataStructure::basicAttributeIDs(CorpusObject::Type type)
{
    QStringList attributeIDs;
    if      (type == CorpusObject::Type_Corpus)
        attributeIDs << "corpusID" << "corpusName" << "description";
    else if (type == CorpusObject::Type_Communication)
        attributeIDs << "communicationID" << "corpusID" << "communicationName";
    else if (type == CorpusObject::Type_Speaker)
        attributeIDs << "speakerID" << "corpusID" << "speakerName";
    else if (type == CorpusObject::Type_Recording)
        attributeIDs << "recordingID" << "communicationID" << "recordingName" << "filename" << "format" << "duration"
                     << "channels" << "sampleRate" << "precisionBits" << "bitRate" << "encoding" << "fileSize" << "checksumMD5";
    else if (type == CorpusObject::Type_Annotation)
        attributeIDs << "annotationID" << "communicationID" << "annotationName" << "recordingID";
    else if (type == CorpusObject::Type_Participation)
        attributeIDs << "corpusID" << "communicationID" << "speakerID" << "role";
    return attributeIDs;
}

// static
QStringList MetadataStructure::basicAttributeNames(CorpusObject::Type type)
{
    QStringList attributeNames;
    if      (type == CorpusObject::Type_Corpus)
        attributeNames << "Corpus ID" << "Corpus Name" << "Description";
    else if (type == CorpusObject::Type_Communication)
        attributeNames << "Communication ID" << "Corpus ID" << "Communication Name";
    else if (type == CorpusObject::Type_Speaker)
        attributeNames << "Speaker ID" << "Corpus ID" << "Speaker Name";
    else if (type == CorpusObject::Type_Recording)
        attributeNames << "Recording ID" << "Communication ID" << "Recording Name" << "Filename" << "Format" << "Duration"
                     << "Channels" << "Sample Rate" << "Precision Bits" << "Bitrate" << "Encoding" << "File Size" << "Checksum MD5";
    else if (type == CorpusObject::Type_Annotation)
        attributeNames << "Annotation ID" << "Communication ID" << "Annotation Name" << "Recording ID";
    else if (type == CorpusObject::Type_Participation)
        attributeNames << "Corpus ID" << "Communication ID" << "Speaker ID" << "Role";
    return attributeNames;
}

QStringList MetadataStructure::allAttributeIDs(CorpusObject::Type what) const
{
    QStringList ret;
    ret << basicAttributeIDs(what);
    if (!m_sections.contains(what)) return ret;
    foreach (MetadataStructureSection *section, m_sections[what]) {
        if (!section) continue;
        ret << section->attributeIDs();
    }
    return ret;
}

QStringList MetadataStructure::allAttributeNames(CorpusObject::Type what) const
{
    QStringList ret;
    ret << basicAttributeNames(what);
    if (!m_sections.contains(what)) return ret;
    foreach (MetadataStructureSection *section, m_sections[what]) {
        if (!section) continue;
        ret << section->attributeNames();
    }
    return ret;
}

PRAALINE_CORE_END_NAMESPACE
