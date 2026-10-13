#ifndef SCN_STEP_ENEMY_CHARAPARAM_H
#define SCN_STEP_ENEMY_CHARAPARAM_H

#include "hel/math/Vec2.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

// TODO: name the members.
struct CharaParam {
    f32 _0;
    // TODO: a hel::math::Vector2 in the original, whose copies are word by word there.
    hel::math::Vec2 _4;
    f32 _c;
    u32 _10;
    u32 _14;
    u32 _18;
    f32 _1c;
    u32 _20;
    u32 _24;
    u32 _28;
    f32 _2c;
    u32 _30;
    f32 _34;
    u32 _38;
    u32 _3c;
    u32 _40;
    bool _44;
    bool _45;
    bool _46;
    bool _47;
    bool _48;
    bool _49;
    bool _4a;
    bool _4b;
    bool _4c;
    bool _4d;
};

}}}  // namespace scn::step::enemy

#endif
