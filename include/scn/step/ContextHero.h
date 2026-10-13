#ifndef SCN_STEP_CONTEXTHERO_H
#define SCN_STEP_CONTEXTHERO_H

#include "scn/step/ContextHeroIndivi.h"
#include "types.h"

namespace scn {
namespace step {

class ContextHero {
public:
    static ContextHero Create();

    ContextHeroIndivi getIndivi(u32 index) const;

    int _0;
    int _4;
    int _8;
    int _C;
    int _10;
    ContextHeroIndivi mIndivi[4];
};

}}  // namespace scn::step

#endif
