#ifndef SCN_STEP_WEAPON_FIGHTERHADOUSHOT_STATEMAIN_H
#define SCN_STEP_WEAPON_FIGHTERHADOUSHOT_STATEMAIN_H

#include "scn/step/weapon/StateBase.h"
#include "scn/step/weapon/fighterhadoushot/Param.h"
#include "scn/step/weapon/fighterhadoushot/Variation.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace fighterhadoushot {

class StateMain : public StateBase {
public:
    StateMain(Weapon* weapon, Variation variation);
    virtual ~StateMain();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual void procObjCollReact();

    void explode();
    const ShotParam& param() const;

private:
    Variation mVariation;
    u32 _C;
};

}
}
}
}

#endif
