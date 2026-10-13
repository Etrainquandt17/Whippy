#ifndef SCN_ARENA_SELECT_SELECTSET_H
#define SCN_ARENA_SELECT_SELECTSET_H

#include "lyt/PaneAccessor.h"
#include "mem/AutoHeapExp.h"
#include "scn/arena/ArenaCursor.h"
#include "types.h"

namespace scn {
namespace arena {
namespace select {

class ChoseData;

class SelectSet {
public:
    u32 getFrame();
    lyt::PaneAccessor getPanel(ArenaCursor cursor);
    ChoseData& chose();
    mem::AutoHeapExp& heap();
};

}}}  // namespace scn::arena::select

#endif
