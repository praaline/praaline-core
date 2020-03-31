#include <QObject>
#include <QString>
#include <QList>
#include <QStringList>
#include <QVariant>
#include <QHash>
#include <QFile>
#include <QTextStream>

#include "PraalineCore/Base/RealTime.h"
#include "PraalineCore/Base/RealValueList.h"
#include "PraalineCore/Annotation/AnnotationDataTable.h"

PRAALINE_CORE_BEGIN_NAMESPACE

AnnotationDataTable::AnnotationDataTable(QObject *parent) :
    QObject(parent)
{
    m_delimiter = "\t";
    m_textQualifier = "";
    m_hasHeaders = true;
}

AnnotationDataTable::~AnnotationDataTable()
{
}

// ==========================================================================================================
// Properties
// ==========================================================================================================

QString AnnotationDataTable::ID() const
{
    return m_ID;
}

void AnnotationDataTable::setID(const QString &ID)
{
    m_ID = ID;
}

QString AnnotationDataTable::delimiter() const
{
    return m_delimiter;
}

void AnnotationDataTable::setDelimiter(const QString &delimiter)
{
    m_delimiter = delimiter;
}

QString AnnotationDataTable::textQualifier() const
{
    return m_textQualifier;
}

void AnnotationDataTable::setTextQualifier(const QString &textQualifier)
{
    m_textQualifier = textQualifier;
}

bool AnnotationDataTable::hasHeaders() const
{
    return m_hasHeaders;
}

void AnnotationDataTable::setHasHeaders(bool hasHeaders)
{
    m_hasHeaders = hasHeaders;
}

// ==========================================================================================================
// Table dimensions
// ==========================================================================================================

int AnnotationDataTable::getRowCount() const
{
    return m_data.count();
}

int AnnotationDataTable::getColumnCount() const
{
    return m_fieldNames.count();
}

// ==========================================================================================================
// Field descriptors
// ==========================================================================================================

QStringList AnnotationDataTable::getFieldNames() const
{
    return m_fieldNames.keys();
}
QStringList AnnotationDataTable::getFieldTypes() const
{
    return m_fieldTypes.values();
}
QString AnnotationDataTable::getFieldType(const QString &fieldname) const
{
    return m_fieldTypes.value(fieldname, "Unknown");
}
QStringList AnnotationDataTable::getFieldDescriptions() const
{
    return m_fieldDescriptions.values();
}
QString AnnotationDataTable::getFieldDescription(const QString &fieldname) const
{
    return m_fieldDescriptions.value(fieldname, "Unknown");
}

// ==========================================================================================================
// Data
// ==========================================================================================================

void AnnotationDataTable::clear()
{
    m_fieldNames.clear();
    m_fieldTypes.clear();
    m_fieldDescriptions.clear();
    m_data.clear();
}

QVariant AnnotationDataTable::getData(int row, int column)
{
    if (row < 0 || row >= m_data.count()) return QVariant();
    if (column < 0 || column >= m_fieldNames.count()) return QVariant();
    return m_data.at(row).at(column);
}

QVariant AnnotationDataTable::getData(int row, const QString &fieldname)
{
    return getData(row, m_fieldNames.value(fieldname, -1));
}

RealTime AnnotationDataTable::getSeconds(int row, const QString &fieldname)
{
    QVariant v = getData(row, m_fieldNames.value(fieldname, -1));
    RealTime r = RealTime::fromSeconds(v.toDouble());
    return r;
}

RealValueList AnnotationDataTable::getValueList(const QString &fieldname)
{
    RealValueList ret;
    for (int row = 0; row < m_data.count(); row++) {
        ret.append(getData(row, fieldname).toDouble());
    }
    return ret;
}

// ==========================================================================================================
// Serialization
// ==========================================================================================================

QString AnnotationDataTable::removeTextQualifiers(const QString input)
{
    QString ret(input);
    if (m_textQualifier.isEmpty()) return ret;
    if (ret.indexOf(m_textQualifier) == 0) ret = ret.remove(0, m_textQualifier.length());
    if (ret.lastIndexOf(m_textQualifier) == ret.length() - 1) ret.chop(m_textQualifier.length());
    return ret;
}


bool AnnotationDataTable::readFromFile(const QString &filename)
{
    // Read tab-separated file
    QFile file(filename);
    if (!file.open( QIODevice::ReadOnly | QIODevice::Text ))
        return false;
    QTextStream stream(&file);
    bool expectHeaderLine = m_hasHeaders;
    do {
        QString line = stream.readLine();
        if (expectHeaderLine) {
            int fieldColumn = 0;
            foreach (QString fieldName, line.split(m_delimiter)) {
                m_fieldNames.insert(removeTextQualifiers(fieldName).trimmed(), fieldColumn);
                fieldColumn++;
            }
            expectHeaderLine = false;
        }
        else {
            QList<QVariant> record;
            foreach (QString value, line.split(m_delimiter)) {
                record.append(QVariant(removeTextQualifiers(value)));
            }
            m_data.append(record);
        }
    } while (!stream.atEnd());
    file.close();
    return true;
}

bool AnnotationDataTable::saveToFile(const QString &filename)
{
    Q_UNUSED(filename)
    return true;
}

PRAALINE_CORE_END_NAMESPACE
