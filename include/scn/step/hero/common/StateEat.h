#ifndef SCN_STEP_HERO_COMMON_STATEEAT_H
#define SCN_STEP_HERO_COMMON_STATEEAT_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

class StateEat : public StateBase {
public:
    StateEat(Hero* hero);
    virtual ~StateEat();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
};

}}}}  // namespace scn::step::hero::common

#endif
