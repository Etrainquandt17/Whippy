#ifndef SCN_STEP_BOSS_FATTYBUFFER_STATETURN_H
#define SCN_STEP_BOSS_FATTYBUFFER_STATETURN_H

#include "scn/step/boss/StateBase.h"

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

class StateTurn : public StateBase {
public:
    StateTurn(Boss* boss);
    virtual ~StateTurn();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::boss::fattybuffer

#endif
