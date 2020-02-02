#ifndef MEASURES_H
#define MEASURES_H

/*
    Praaline - Core module - Statistics
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
#include <QPair>

#include "PraalineCore/PraalineCore_Global.h"
#include "PraalineCore/Base/RealTime.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class IntervalTier;

class PRAALINE_CORE_SHARED_EXPORT Measures
{
public:
    static QPair<int, int> window(IntervalTier *tier, int i, int windowLeft, int windowRight, bool pauseBlocksWindow = true);
    static QPair<int, int> window(IntervalTier *tier, RealTime centre, RealTime windowLeft, RealTime windowRight, bool pauseBlocksWindow);

    static bool mean(double &mean, IntervalTier *tier, QString attributeName, int i, int windowLeft, int windowRight,
                     bool pauseBlocksWindow = true, QString checkAttribute = QString());
    static double mean(IntervalTier *tier, QString attributeName, int i, int windowLeft, int windowRight,
                       bool pauseBlocksWindow = true, QString checkAttribute = QString());

    static double relative(IntervalTier *tier, QString attributeName, int i, int windowLeft, int windowRight,
                           bool pauseBlocksWindow = true, QString checkAttribute = QString(), bool logarithmic = false);

    static int quantize(double x, int factor, int max);

private:
    Measures() {}
};

PRAALINE_CORE_END_NAMESPACE

#endif // MEASURES_H
