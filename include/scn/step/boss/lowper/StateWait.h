#ifndef SCN_STEP_BOSS_LOWPER_STATEWAIT_H
#define SCN_STEP_BOSS_LOWPER_STATEWAIT_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

class StateWait : public StateBase {
public:
    StateWait(Boss* boss);
    StateWait(Boss* boss, const hel::math::Vector3& offset);
    virtual ~StateWait();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void commonInit(const hel::math::Vector3& pos);
};

}}}}  // namespace scn::step::boss::lowper

#endif
