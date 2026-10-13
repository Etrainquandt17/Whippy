#ifndef SCN_STEP_BOSS_MAHOROABATTLE2_MAGICBALLCTRL_H
#define SCN_STEP_BOSS_MAHOROABATTLE2_MAGICBALLCTRL_H

#include "hel/math/Vec2.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace mahoroabattle2 {

// TODO: members.
class MagicBallCtrl {
public:
    struct ReqData {
        // TODO: _C is probably a vector class whose inline constructor does this.
        ReqData() { _C.x = _C.y = 0.0f; }

        u32 _0;
        u32 _4;
        u32 _8;
        hel::math::Vec2 _C;
    };

    void addReqData(const ReqData& data);
    void clearReqData();
};

}}}}  // namespace scn::step::boss::mahoroabattle2

#endif
