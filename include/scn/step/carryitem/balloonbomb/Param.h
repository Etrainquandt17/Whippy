#ifndef SCN_STEP_CARRYITEM_BALLOONBOMB_PARAM_H
#define SCN_STEP_CARRYITEM_BALLOONBOMB_PARAM_H

#include "types.h"

namespace scn {
namespace step {
namespace carryitem {
namespace balloonbomb {

// TODO: name the members; the ones not seen in use yet are taken to be words.
struct Param {
    u32 _0[0x50 / 4];
    u32 _50;
    u32 _54;
};

}}}}  // namespace scn::step::carryitem::balloonbomb

#endif
