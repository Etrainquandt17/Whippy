#ifndef SCN_STEP_BOSS_GOLIATH_STATEPUNCHCHARGE_H
#define SCN_STEP_BOSS_GOLIATH_STATEPUNCHCHARGE_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace goliath {

// TODO: members.
class StatePunchCharge : public IState {
public:
    StatePunchCharge(Boss* boss, u32 _1, u32 _2, bool _3);
    virtual ~StatePunchCharge();
};

}}}}  // namespace scn::step::boss::goliath

#endif
