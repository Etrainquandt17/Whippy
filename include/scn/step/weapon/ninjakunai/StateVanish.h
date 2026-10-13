#ifndef SCN_STEP_WEAPON_NINJAKUNAI_STATEVANISH_H
#define SCN_STEP_WEAPON_NINJAKUNAI_STATEVANISH_H

#include "scn/step/weapon/StateBase.h"
#include "scn/step/weapon/ninjakunai/Param.h"
#include "scn/step/weapon/ninjakunai/VanishKind.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace ninjakunai {

class StateVanish : public StateBase {
public:
    StateVanish(Weapon* weapon, VanishKind kind);
    virtual ~StateVanish();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual void procObjCollReact();

private:
    bool isRoll() const;
    const Param::Vanish& param() const;

    u32 mFrame;
    f32 mRot;
    VanishKind mKind;
    f32 mRotSign;
};

}}}}  // namespace scn::step::weapon::ninjakunai

#endif
