#include <QString>
#include <QList>
#include <QVector>

#include "PraalineCore/Annotation/Interval.h"
#include "PraalineCore/Diff/dtl/dtl.h"
using dtl::Diff;
#include "PraalineCore/Diff/DiffIntervals.h"

PRAALINE_CORE_BEGIN_NAMESPACE

CompareInterval::CompareInterval(bool compareBoundaries, const QString &attributeID_A, const QString &attributeID_B) :
    m_compareBoundaries(compareBoundaries), m_attributeID_A(attributeID_A), m_attributeID_B(attributeID_B)
{}

CompareInterval::CompareInterval(const CompareInterval &other) :
    m_compareBoundaries(other.m_compareBoundaries), m_attributeID_A(other.m_attributeID_A), m_attributeID_B(other.m_attributeID_B)
{
}

CompareInterval::~CompareInterval()
{}

bool CompareInterval::impl (Interval * const& e1, Interval * const& e2) const {
    bool ret;
    ret = (m_compareBoundaries) ? (e1->tMin() == e2->tMin() && e1->tMax() == e2->tMax()) : true;
    if (m_attributeID_A.isEmpty() && m_attributeID_B.isEmpty())
        ret = ret && (e1->text() == e2->text());
    else if (!m_attributeID_A.isEmpty() && !m_attributeID_B.isEmpty())
        ret = ret && (e1->attribute(m_attributeID_A) == e2->attribute(m_attributeID_B));
    else if (m_attributeID_A.isEmpty())
        ret = ret && (e1->text() == e2->attribute(m_attributeID_B).toString());
    else if (m_attributeID_B.isEmpty())
        ret = ret && (e1->attribute(m_attributeID_A).toString() == e2->text());
    return ret;
}


DiffIntervals::DiffIntervals()
{
}

DiffIntervals::~DiffIntervals()
{
}

Diff<std::string> DiffIntervals::stringDiff(QList<Interval *> listA, QList<Interval *> listB,
                                            QString attributeID_A, QString attributeID_B)
{
    std::vector<std::string> sequenceA;
    std::vector<std::string> sequenceB;
    foreach (Interval *intvA, listA) {
        std::string A = (attributeID_A.isEmpty()) ? intvA->text().toStdString()
                                                  : intvA->attribute(attributeID_A).toString().toStdString();
        sequenceA.push_back(A);
    }
    foreach (Interval *intvB, listB) {
        std::string B = (attributeID_B.isEmpty()) ? intvB->text().toStdString()
                                                  : intvB->attribute(attributeID_B).toString().toStdString();
        sequenceA.push_back(B);
    }
    Diff<std::string> d(sequenceA, sequenceB);
    d.compose();
    return d;
}

Diff<Interval *, std::vector<Interval *>, CompareInterval>
DiffIntervals::intervalDiff(QList<Interval *> listA, QList<Interval *> listB, bool compareBoundaries,
                            QString attributeID_A, QString attributeID_B)
{
    std::vector<Interval *> sequenceA = std::vector<Interval *>(listA.toVector().begin(), listA.toVector().end());
    std::vector<Interval *> sequenceB = std::vector<Interval *>(listB.toVector().begin(), listB.toVector().end());
    CompareInterval comparator(compareBoundaries, attributeID_A, attributeID_B);
    Diff<Interval *, std::vector<Interval *>, CompareInterval> d(sequenceA, sequenceB, false, comparator);
    d.compose();
    return d;
}

QString DiffIntervals::diffTable(Diff<Interval *, std::vector<Interval *>, CompareInterval> &diff)
{
    QString ret;
    dtl::Ses<Interval *> ses = diff.getSes();
    dtl::Ses<Interval *>::sesElemVec sesElemVec = ses.getSequence();
    for (size_t i = 0; i < sesElemVec.size(); ++i) {
        dtl::edit_t editType = sesElemVec[i].second.type;
        Interval *intv = sesElemVec[i].first;
        if (editType == dtl::SES_COMMON)
            ret.append("=\t").append(intv->text()).append("\t").append(intv->text()).append("\n");
        else if (editType == dtl::SES_DELETE)
            ret.append("-\t").append(intv->text()).append("\t").append("").append("\n");
        else
            ret.append("+\t").append("").append("\t").append(intv->text()).append("\n");
    }
    return ret;
}

PRAALINE_CORE_END_NAMESPACE
