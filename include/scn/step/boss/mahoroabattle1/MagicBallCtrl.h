#ifndef SCN_STEP_BOSS_MAHOROABATTLE1_MAGICBALLCTRL_H
#define SCN_STEP_BOSS_MAHOROABATTLE1_MAGICBALLCTRL_H

#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace mahoroabattle1 {

// TODO: members.
class MagicBallCtrl {
public:
    struct ReqData {
        u32 _0;
        u32 _4;
    };

    void addReqData(u32 _1, const ReqData& data);
    void clearReqData();
};

}}}}  // namespace scn::step::boss::mahoroabattle1

#endif
