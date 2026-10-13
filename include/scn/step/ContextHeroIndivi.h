#ifndef SCN_STEP_CONTEXTHEROINDIVI_H
#define SCN_STEP_CONTEXTHEROINDIVI_H

#include "types.h"

namespace scn {
namespace step {

class ContextHeroIndivi {
public:
    struct PlayRecord {
        u32 _0;
        u32 _4;
    };
    typedef PlayRecord Unk38;

    static ContextHeroIndivi Create();
    static ContextHeroIndivi CreateDefault();

    int _0;
    int _4;
    u32 _8[12];
    Unk38 _38;
};

}}  // namespace scn::step

#endif
