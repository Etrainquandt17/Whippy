#ifndef SCN_STEP_WEAPON_FIGHTERHADOUSHOT_STATEEXPLOSION_H
#define SCN_STEP_WEAPON_FIGHTERHADOUSHOT_STATEEXPLOSION_H

#include "scn/step/weapon/StateBase.h"
#include "scn/step/weapon/fighterhadoushot/Param.h"
#include "scn/step/weapon/fighterhadoushot/Variation.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace fighterhadoushot {

class StateExplosion : public StateBase {
public:
    StateExplosion(Weapon* weapon, Variation variation);
    virtual ~StateExplosion();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual void procObjCollReact();

    const ExplosionParam& param() const;

private:
    Variation mVariation;
    u32 _C;
};

}}}}  // namespace scn::step::weapon::fighterhadoushot

#endif
