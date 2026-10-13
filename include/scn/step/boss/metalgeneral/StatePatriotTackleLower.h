#ifndef SCN_STEP_BOSS_METALGENERAL_STATEPATRIOTTACKLELOWER_H
#define SCN_STEP_BOSS_METALGENERAL_STATEPATRIOTTACKLELOWER_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

// TODO: members.
class StatePatriotTackleLower : public StateBase {
public:
    StatePatriotTackleLower(Boss* boss);
    virtual ~StatePatriotTackleLower();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::boss::metalgeneral

#endif
