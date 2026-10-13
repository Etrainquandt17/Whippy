#ifndef SCN_STEP_HERO_COMMON_STATECARRYITEMPUT_H
#define SCN_STEP_HERO_COMMON_STATECARRYITEMPUT_H

#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

class StateCarryItemPut : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateCarryItemPut(Hero* hero);
    virtual ~StateCarryItemPut();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    bool mIsTrigger1;
};

}}}}  // namespace scn::step::hero::common

#endif
