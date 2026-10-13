#ifndef SCN_STEP_BOSS_HRD3PILOT_TAILCTRL_H
#define SCN_STEP_BOSS_HRD3PILOT_TAILCTRL_H

#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace hrd3pilot {

}
class Boss;
namespace hrd3pilot {

class TailCtrl {
public:
    TailCtrl(Boss& boss);

    void update();
    void storage();
    void extract();

private:
    Boss& mBoss;
    bool mIsStored;
    u32 mCount;
};

}}}}  // namespace scn::step::boss::hrd3pilot

#endif
