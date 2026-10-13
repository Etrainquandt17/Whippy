#ifndef SCN_STEP_BOSS_LOWPER_STATEHIDE_H
#define SCN_STEP_BOSS_LOWPER_STATEHIDE_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

class StateHide : public StateBase {
public:
    StateHide(Boss* boss);
    virtual ~StateHide();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::boss::lowper

#endif
