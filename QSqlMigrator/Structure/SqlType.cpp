#include "base/DataType.h"
#include "SqlType.h"

namespace QSqlMigrator {
namespace Structure {

SqlType::SqlType(SqlType::Base base, quint64 precision, int scale) :
    m_base(base),
    m_precision(precision),
    m_scale(scale)
{
}

SqlType::SqlType(const QString &string) :
    m_base(Invalid),
    m_precision(0),
    m_scale(0),
    m_string(string)
{
}

SqlType::SqlType(const PRAALINE_CORE_NAMESPACE::DataType& datatype) :
    m_base(Invalid),
    m_precision(datatype.precision()),
    m_scale(datatype.scale())
{
    switch (datatype.base()) {
    case PRAALINE_CORE_NAMESPACE::DataType::Invalid:     m_base = SqlType::Invalid;  break;
    case PRAALINE_CORE_NAMESPACE::DataType::Char:        m_base = SqlType::Char;     break;
    case PRAALINE_CORE_NAMESPACE::DataType::VarChar:     m_base = SqlType::VarChar;  break;
    case PRAALINE_CORE_NAMESPACE::DataType::Binary:      m_base = SqlType::Binary;   break;
    case PRAALINE_CORE_NAMESPACE::DataType::VarBinary:   m_base = SqlType::VarBinary;break;
    case PRAALINE_CORE_NAMESPACE::DataType::Boolean:     m_base = SqlType::Boolean;  break;
    case PRAALINE_CORE_NAMESPACE::DataType::SmallInt:    m_base = SqlType::SmallInt; break;
    case PRAALINE_CORE_NAMESPACE::DataType::Integer:     m_base = SqlType::Integer;  break;
    case PRAALINE_CORE_NAMESPACE::DataType::BigInt:      m_base = SqlType::BigInt;   break;
    case PRAALINE_CORE_NAMESPACE::DataType::Decimal:     m_base = SqlType::Decimal;  break;
    case PRAALINE_CORE_NAMESPACE::DataType::Float:       m_base = SqlType::Float;    break;
    case PRAALINE_CORE_NAMESPACE::DataType::Double:      m_base = SqlType::Double;   break;
    case PRAALINE_CORE_NAMESPACE::DataType::Date:        m_base = SqlType::Date;     break;
    case PRAALINE_CORE_NAMESPACE::DataType::Time:        m_base = SqlType::Time;     break;
    case PRAALINE_CORE_NAMESPACE::DataType::DateTime:    m_base = SqlType::Timestamp;break;
    case PRAALINE_CORE_NAMESPACE::DataType::Interval:    m_base = SqlType::Interval; break;
    case PRAALINE_CORE_NAMESPACE::DataType::Array:       m_base = SqlType::Array;    break;
    case PRAALINE_CORE_NAMESPACE::DataType::Multiset:    m_base = SqlType::Multiset; break;
    case PRAALINE_CORE_NAMESPACE::DataType::Xml:         m_base = SqlType::Xml;      break;
    case PRAALINE_CORE_NAMESPACE::DataType::Geometry:    m_base = SqlType::Xml;      break;
    }
}

bool SqlType::isBaseType() const
{
    return m_base != Invalid;
}

bool SqlType::isString() const
{
    return m_base == Invalid && (!m_string.isEmpty());
}

bool SqlType::isValid() const
{
    return m_base != Invalid || (!m_string.isEmpty());
}

const QString &SqlType::string() const
{
    return m_string;
}

SqlType::Base SqlType::base() const {
    return m_base;
}

quint64 SqlType::precision(quint64 defaultValue) const {
    if( 0 == m_precision )
        return defaultValue;
    return m_precision;
}

int SqlType::scale() const {
    return m_scale;
}

const SqlType &SqlType::invalid()
{
    static SqlType invalid_sql_type(SqlType::Invalid);
    return invalid_sql_type;
}

} // namespace Structure
} // namespace QSqlMigrator
