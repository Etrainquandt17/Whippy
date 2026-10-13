#ifndef SCN_STEP_BOSS_KINGSDOO_STATECHARGEATTACK_H
#define SCN_STEP_BOSS_KINGSDOO_STATECHARGEATTACK_H

#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/kingsdoo/StateChargeAttackStart.h"

namespace scn {
namespace step {
namespace boss {
namespace kingsdoo {

class StateChargeAttack : public StateBase {
public:
    struct Config {
        bool _0;
        bool _1;
    };

    StateChargeAttack(Boss* boss, Config config);
    virtual ~StateChargeAttack();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void reqWaveShot();

    Config mConfig;
};

}}}}  // namespace scn::step::boss::kingsdoo

#endif
