#ifndef SCN_STEP_BOSS_DUBIOR_STATETHUNDER_H
#define SCN_STEP_BOSS_DUBIOR_STATETHUNDER_H

#include "scn/step/boss/StateBase.h"

namespace scn {
namespace step {
namespace boss {
namespace dubior {

class StateThunder : public StateBase {
public:
    StateThunder(Boss* boss);
    virtual ~StateThunder();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::boss::dubior

#endif
