#ifndef SCN_STEP_HERO_EFFECT_H
#define SCN_STEP_HERO_EFFECT_H

#include "scn/step/chara/Effect.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {

class Effect {
public:
    // TODO: name. Where the original reaches a member through an inline accessor, the arguments are evaluated
    // behind effect() (interference::StateHang's constructor).
    chara::Effect& get_8() { return _8; }

    u32 _0[2];
    chara::Effect _8;
    chara::Effect _30;
    chara::Effect _58;
    chara::Effect _80;
    chara::Effect _A8;
    chara::Effect _D0;
    chara::Effect _F8;
    chara::Effect _120;
    chara::Effect _148;
    chara::Effect _170;
    chara::Effect _198;
    chara::Effect _1C0;
    chara::Effect _1E8;
    chara::Effect _210;
};

}
}
}

#endif
