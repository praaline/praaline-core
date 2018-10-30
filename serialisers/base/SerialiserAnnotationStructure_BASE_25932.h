#ifndef SERIALISERANNOTATIONSTRUCTURE_H
#define SERIALISERANNOTATIONSTRUCTURE_H

/*
    Praaline - Core module - Serialisers
    Copyright (c) 2011-2018 George Christodoulides

    This program or module is free software: you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation, either version 3 of
    the License, or (at your option) any later version. It is provided
    for educational purposes and is distributed in the hope that it will
    be useful, but WITHOUT ANY WARRANTY; without even the implied
    warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See
    the GNU General Public License for more details.
*/

#include "pncore_global.h"
#include <QString>
#include "structure/AnnotationStructure.h"

namespace Praaline {
namespace Core {

class SerialiserAnnotationStructure
{
protected:
    SerialiserAnnotationStructure() {}
    virtual ~SerialiserAnnotationStructure() {}

    static QString convertLevelTypeToString(AnnotationStructureLevel::LevelType levelType);
    static AnnotationStructureLevel::LevelType convertStringToLevelType(QString str);
};

} // namespace Core
} // namespace Praaline

#endif // SERIALISERANNOTATIONSTRUCTURE_H
