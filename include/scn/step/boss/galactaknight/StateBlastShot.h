#ifndef SCN_STEP_BOSS_GALACTAKNIGHT_STATEBLASTSHOT_H
#define SCN_STEP_BOSS_GALACTAKNIGHT_STATEBLASTSHOT_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

class StateBlastShot : public StateBase {
public:
    StateBlastShot(Boss* boss);
    virtual ~StateBlastShot();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void generateBlastShot();
};

}}}}  // namespace scn::step::boss::galactaknight

#endif
