#ifndef SCN_STEP_WEAPON_NINJAKUNAI_STATESTICKENEMY_H
#define SCN_STEP_WEAPON_NINJAKUNAI_STATESTICKENEMY_H

#include "scn/step/weapon/StateBase.h"
#include "scn/step/weapon/StickEnemyAlgorithm.h"
#include "types.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace weapon {
namespace ninjakunai {

class StateStickEnemy : public StateBase {
public:
    StateStickEnemy(Weapon* weapon, const util::ObjRefHandle<enemy::Enemy>& enemy);
    virtual ~StateStickEnemy();
    virtual void procAnim();
    virtual void procMove();
    virtual void procConstraint();

private:
    StickEnemyAlgorithm mAlgorithm;
    u32 mFrame;
};

}}}}  // namespace scn::step::weapon::ninjakunai

#endif
