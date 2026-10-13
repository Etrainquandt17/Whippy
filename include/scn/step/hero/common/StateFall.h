#ifndef SCN_STEP_HERO_COMMON_STATEFALL_H
#define SCN_STEP_HERO_COMMON_STATEFALL_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

class StateFall : public StateBase {
public:
    StateFall(Hero* hero);
    StateFall(Hero* hero, bool);
    virtual ~StateFall();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void construct();

    bool _8;
    u32 mFrame;
    f32 mFallLength;
    bool mIsPassThroughLand;
};

}}}}  // namespace scn::step::hero::common

#endif
