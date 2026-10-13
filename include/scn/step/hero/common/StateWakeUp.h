#ifndef SCN_STEP_HERO_COMMON_STATEWAKEUP_H
#define SCN_STEP_HERO_COMMON_STATEWAKEUP_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

class StateWakeUp : public StateBase {
public:
    StateWakeUp(Hero* hero, bool isPauseDisable);
    virtual ~StateWakeUp();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    bool mIsPauseDisable;
};

}}}}  // namespace scn::step::hero::common

#endif
