#ifndef SCN_STEP_CARRYITEM_LOCKKEY_PARAM_H
#define SCN_STEP_CARRYITEM_LOCKKEY_PARAM_H

#include "types.h"

namespace scn {
namespace step {
namespace carryitem {
namespace lockkey {

// TODO: name the members; the ones not seen in use yet are taken to be words.
struct Param {
    u32 _0;
    u32 _4;
    u32 _8;
    f32 _C;
    f32 _10;
    f32 _14;
    u32 _18;
    u32 _1C;
    u32 _20;
};

}}}}  // namespace scn::step::carryitem::lockkey

#endif
