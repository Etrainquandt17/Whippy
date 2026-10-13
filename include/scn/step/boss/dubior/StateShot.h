#ifndef SCN_STEP_BOSS_DUBIOR_STATESHOT_H
#define SCN_STEP_BOSS_DUBIOR_STATESHOT_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace dubior {

class StateShot : public StateBase {
public:
    StateShot(Boss* boss, f32 angle);
    virtual ~StateShot();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void reqShot();

    f32 mAngle;
};

}}}}  // namespace scn::step::boss::dubior

#endif
