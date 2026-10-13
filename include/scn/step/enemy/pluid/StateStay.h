#ifndef SCN_STEP_ENEMY_PLUID_STATESTAY_H
#define SCN_STEP_ENEMY_PLUID_STATESTAY_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace pluid {

class StateStay : public StateBase {
public:
    StateStay(Enemy* enemy);
    virtual ~StateStay();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    bool isPlayerNear();
    void isExistLand();
    
    bool mIsExistLand;
    bool _9;
    u32 mFrame;
    u32 mWaitFrame;
    u32 mFallFrame;
};

}}}}  // namespace scn::step::enemy::pluid

#endif
