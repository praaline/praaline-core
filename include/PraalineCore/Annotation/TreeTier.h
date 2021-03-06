#ifndef TREETIER_H
#define TREETIER_H

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

#include <QObject>
#include "PraalineCore/PraalineCore_Global.h"
#include "PraalineCore/Annotation/AnnotationTier.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class PRAALINE_CORE_SHARED_EXPORT TreeTier : public AnnotationTier
{
    Q_OBJECT
public:
    explicit TreeTier(QObject *parent = nullptr);
    ~TreeTier();

signals:

public slots:
};

PRAALINE_CORE_END_NAMESPACE

#endif // TREETIER_H
