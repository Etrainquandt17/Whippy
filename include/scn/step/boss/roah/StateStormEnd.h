#ifndef SCN_STEP_BOSS_ROAH_STATESTORMEND_H
#define SCN_STEP_BOSS_ROAH_STATESTORMEND_H

#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/roah/StateStorm.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace roah {

class StateStormEnd : public StateBase {
public:
    struct Config {
        StormKind mKind;
        f32 mRotX;
    };

    StateStormEnd(Boss* boss, Config config);
    virtual ~StateStormEnd();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    Config mConfig;
};

}}}}  // namespace scn::step::boss::roah

#endif
