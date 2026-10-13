#ifndef SCN_STEP_HERO_COMMON_STATESUPERJUMP_H
#define SCN_STEP_HERO_COMMON_STATESUPERJUMP_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

class StateSuperJump : public StateBase {
public:
    StateSuperJump(Hero* hero);
    virtual ~StateSuperJump();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    bool mIsFall;
};

}}}}  // namespace scn::step::hero::common

#endif
