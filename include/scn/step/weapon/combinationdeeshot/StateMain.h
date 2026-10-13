#ifndef SCN_STEP_WEAPON_COMBINATIONDEESHOT_STATEMAIN_H
#define SCN_STEP_WEAPON_COMBINATIONDEESHOT_STATEMAIN_H

#include "scn/step/ocoll/AttackType.h"
#include "scn/step/weapon/StateBase.h"
#include "scn/step/weapon/combinationdeeshot/Param.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace combinationdeeshot {

class StateMain : public StateBase {
public:
    StateMain(Weapon* weapon);
    virtual ~StateMain();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual void procObjCollReact();

    const LevelParam& param() const;
    const ocoll::AttackType& attackType() const;

private:
    u32 _8;
};

}
}
}
}

#endif
