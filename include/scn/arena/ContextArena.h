#ifndef SCN_ARENA_CONTEXTARENA_H
#define SCN_ARENA_CONTEXTARENA_H

#include "scn/arena/select/ChoseData.h"
#include "types.h"

namespace scn {
namespace arena {

class ContextArena {
public:
    ContextArena& operator=(const ContextArena& other);

    u8 _0[0xB0];
    select::ChoseData::ArenaDataPlayer _B0;
    u8 _E4[0x258 - 0xE4];
};

}}  // namespace scn::arena

#endif
