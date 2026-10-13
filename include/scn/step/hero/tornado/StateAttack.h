#ifndef SCN_STEP_HERO_TORNADO_STATEATTACK_H
#define SCN_STEP_HERO_TORNADO_STATEATTACK_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace tornado {

struct ParamTornadoMove;
class StateAttack : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateAttack(Hero* hero);
    virtual ~StateAttack();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual bool procObjCollReact();

private:
    void tornadoMove(const ParamTornadoMove& param);
    void turn();
    void updateDustEffect();
    void setEnableCharge();
    void updateCharge();
    bool tryToChangeChargeAttack();

    u32 mTurnWait;
    u32 mDustWait;
    bool mIsCharged;
    bool mIsEnd;
};

}}}}  // namespace scn::step::hero::tornado

#endif
