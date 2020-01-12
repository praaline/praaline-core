#include <QString>
#include <QList>
#include <QVector>

#include "annotation/Point.h"
#include "diff/dtl/dtl.h"
using dtl::Diff;
#include "diff/DiffPoints.h"

PRAALINE_CORE_BEGIN_NAMESPACE

ComparePoint::ComparePoint(bool compareTimes, const QString &attributeID_A, const QString &attributeID_B) :
    m_compareTimes(compareTimes), m_attributeID_A(attributeID_A), m_attributeID_B(attributeID_B)
{}

ComparePoint::ComparePoint(const ComparePoint &other) :
    m_compareTimes(other.m_compareTimes), m_attributeID_A(other.m_attributeID_A), m_attributeID_B(other.m_attributeID_B)
{
}

ComparePoint::~ComparePoint()
{}

bool ComparePoint::impl (Point * const& e1, Point * const& e2) const {
    bool ret;
    ret = (m_compareTimes) ? (e1->time() == e2->time()) : true;
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


DiffPoints::DiffPoints()
{
}

DiffPoints::~DiffPoints()
{
}

Diff<std::string> DiffPoints::stringDiff(QList<Point *> listA, QList<Point *> listB,
                                         QString attributeID_A, QString attributeID_B)
{
    std::vector<std::string> sequenceA;
    std::vector<std::string> sequenceB;
    foreach (Point *intvA, listA) {
        std::string A = (attributeID_A.isEmpty()) ? intvA->text().toStdString()
                                                  : intvA->attribute(attributeID_A).toString().toStdString();
        sequenceA.push_back(A);
    }
    foreach (Point *intvB, listB) {
        std::string B = (attributeID_B.isEmpty()) ? intvB->text().toStdString()
                                                  : intvB->attribute(attributeID_B).toString().toStdString();
        sequenceA.push_back(B);
    }
    Diff<std::string> d(sequenceA, sequenceB);
    d.compose();
    return d;
}

Diff<Point *, std::vector<Point *>, ComparePoint>
DiffPoints::PointDiff(QList<Point *> listA, QList<Point *> listB, bool compareBoundaries,
                            QString attributeID_A, QString attributeID_B)
{
    std::vector<Point *> sequenceA = std::vector<Point *>(listA.toVector().begin(), listA.toVector().end());
    std::vector<Point *> sequenceB = std::vector<Point *>(listB.toVector().begin(), listB.toVector().end());
    ComparePoint comparator(compareBoundaries, attributeID_A, attributeID_B);
    Diff<Point *, std::vector<Point *>, ComparePoint> d(sequenceA, sequenceB, false, comparator);
    d.compose();
    return d;
}

QString DiffPoints::diffTable(Diff<Point *, std::vector<Point *>, ComparePoint> &diff)
{
    QString ret;
    dtl::Ses<Point *> ses = diff.getSes();
    dtl::Ses<Point *>::sesElemVec sesElemVec = ses.getSequence();
    for (size_t i = 0; i < sesElemVec.size(); ++i) {
        dtl::edit_t editType = sesElemVec[i].second.type;
        Point *intv = sesElemVec[i].first;
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
