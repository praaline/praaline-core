#include <math.h>
#include <QList>
#include "base/RealValueList.h"

RealValueList::RealValueList()
{
    m_mean = 0.0;
    m_M2 = 0.0;
    m_sum = 0.0;
}

void RealValueList::recalculate()
{
    m_mean = 0.0;
    m_M2 = 0.0;
    m_sum = 0.0;
    foreach(double x, *this) {
        double delta = x - m_mean;
        m_mean += delta / static_cast<double>(count());
        m_M2 += delta * (x - m_mean);
        m_sum += x;
    }
}

void RealValueList::append(const double &x)
{
    QList<double>::append(x);
    double delta = x - m_mean;
    m_mean += delta / static_cast<double>(count());
    m_M2 += delta * (x - m_mean);
    m_sum += x;
}

double RealValueList::mean() const
{
    return m_mean;
}
double RealValueList::variance() const
{
    return m_M2 / static_cast<double>((count() - 1));
}
double RealValueList::stddev() const
{
    return sqrt(variance());
}
double RealValueList::sum() const
{
    return m_sum;
}

double RealValueList::zscore(int i) const
{
    if ((i < 0) || (i >= count()))
        return 0.0;
    return (at(i) - mean()) / stddev();
}

double RealValueList::zscore_calculate(double x) const
{
    return (x - mean()) / stddev();
}
