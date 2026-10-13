#ifndef SCN_STEP_BOSS_LANDIA_STATETAIL_H
#define SCN_STEP_BOSS_LANDIA_STATETAIL_H

#include "hel/math/Vector2.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace landia {

class StateTail : public StateBase {
public:
    struct Config {
        int _0;
    };

    StateTail(Boss* boss, Config config);
    virtual ~StateTail();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void reqStar();

    u32 mCount;
    hel::math::Vector2 mStartPos;
    hel::math::Vector2 mGoalPos;
    bool mIsMove;
};

}}}}  // namespace scn::step::boss::landia

#endif
