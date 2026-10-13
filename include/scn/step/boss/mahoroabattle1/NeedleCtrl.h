#ifndef SCN_STEP_BOSS_MAHOROABATTLE1_NEEDLECTRL_H
#define SCN_STEP_BOSS_MAHOROABATTLE1_NEEDLECTRL_H

#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace mahoroabattle1 {

// TODO: members.
class NeedleCtrl {
public:
    void addReqBuff(u32 _1, f32 _2);
    void clearBuff();
    void request(u32 _1);
    void reqStateStart(u32 _1);
};

}}}}  // namespace scn::step::boss::mahoroabattle1

#endif
