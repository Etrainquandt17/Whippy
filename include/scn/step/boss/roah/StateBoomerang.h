#ifndef SCN_STEP_BOSS_ROAH_STATEBOOMERANG_H
#define SCN_STEP_BOSS_ROAH_STATEBOOMERANG_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace roah {

class StateBoomerang : public StateBase {
public:
    struct Config {
        int _0;
    };

    StateBoomerang(Boss* boss, Config config);
    virtual ~StateBoomerang();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    bool mIsThrown;
    bool mIsCaught;
    Config mConfig;
};

}}}}  // namespace scn::step::boss::roah

#endif
