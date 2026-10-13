#ifndef SCN_STEP_HERO_COMMON_STATEWALK_H
#define SCN_STEP_HERO_COMMON_STATEWALK_H

#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

class StateWalk : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateWalk(Hero* hero);
    virtual ~StateWalk();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    bool mIsVacuum;
};

}}}}  // namespace scn::step::hero::common

#endif
