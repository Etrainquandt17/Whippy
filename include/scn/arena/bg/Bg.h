#ifndef SCN_ARENA_BG_BG_H
#define SCN_ARENA_BG_BG_H

#include "scn/arena/bg/desc/BgName.h"
#include "types.h"

namespace scn {
namespace arena {

class RenderSet;

namespace bg {

class Bg {
public:
    Bg(RenderSet& renderSet, desc::BgName name);
    ~Bg();

private:
    u32 _0[0x128];
};

}}}  // namespace scn::arena::bg

#endif
