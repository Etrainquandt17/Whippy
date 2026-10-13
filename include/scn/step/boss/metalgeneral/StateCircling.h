#ifndef SCN_STEP_BOSS_METALGENERAL_STATECIRCLING_H
#define SCN_STEP_BOSS_METALGENERAL_STATECIRCLING_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

class StateCircling : public StateBase {
public:
    StateCircling(Boss* boss);
    virtual ~StateCircling();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    hel::math::Vector3 mStartPos;
};

}}}}  // namespace scn::step::boss::metalgeneral

#endif
