#ifndef DATASTORE_H
#define DATASTORE_H

/*
    Praaline - Core module - Base
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

#include "PraalineCore/PraalineCore_Global.h"
#include "PraalineCore/Base/ISaveable.h"

PRAALINE_CORE_BEGIN_NAMESPACE

// Internal interface
class PRAALINE_CORE_SHARED_EXPORT IDatastore {
public:
    IDatastore();
    virtual ~IDatastore();

protected:
    static void setNew(ISaveable *item)    { item->m_isNew = true;    }
    static void setDirty(ISaveable *item)  { item->m_isDirty = true;  }
    static void setClean(ISaveable *item)  { item->m_isNew = false;
                                             item->m_isDirty = false; }
};

PRAALINE_CORE_END_NAMESPACE

#endif // DATASTORE_H
