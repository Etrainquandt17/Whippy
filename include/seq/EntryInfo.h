#ifndef SEQ_ENTRYINFO_H
#define SEQ_ENTRYINFO_H

#include "types.h"

namespace seq {

struct EntryInfo {
    static EntryInfo Create();

    u32 _0[4];
};

}

#endif
