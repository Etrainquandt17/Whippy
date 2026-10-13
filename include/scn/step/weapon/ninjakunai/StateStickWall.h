#ifndef SCN_STEP_WEAPON_NINJAKUNAI_STATESTICKWALL_H
#define SCN_STEP_WEAPON_NINJAKUNAI_STATESTICKWALL_H

#include "scn/step/weapon/StateBase.h"
#include "scn/step/weapon/StickWallAlgorithm.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace ninjakunai {

class StateStickWall : public StateBase {
public:
    StateStickWall(Weapon* weapon);
    virtual ~StateStickWall();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual void procObjCollReact();

private:
    StickWallAlgorithm mAlgorithm;
    u32 mFrame;
};

}}}}  // namespace scn::step::weapon::ninjakunai

#endif
