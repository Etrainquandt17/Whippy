#ifndef SCN_STEP_HERO_SOUNDSE_H
#define SCN_STEP_HERO_SOUNDSE_H

#include "snd/SERequestor.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {

class SoundSE {
public:
    snd::SERequestor& get_4() { return _4; }

    u32 _0;
    snd::SERequestor _4;
    snd::SERequestor _78;
    snd::SERequestor _EC;
    snd::SERequestor _160;
    snd::SERequestor _1D4;
    snd::SERequestor _248;
    snd::SERequestor _2BC;
    snd::SERequestor _330;
};

}}}  // namespace scn::step::hero

#endif
