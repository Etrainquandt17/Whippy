#ifndef SCN_STEP_WEAPON_STATEBASE_H
#define SCN_STEP_WEAPON_STATEBASE_H

#include "scn/step/weapon/IState.h"

namespace scn {
namespace step {
namespace weapon {

class Weapon;

// TODO: the functions are IState's, which does not declare them yet.
class StateBase : public IState {
public:
    StateBase(Weapon* weapon);
    virtual ~StateBase();
    virtual void procAnim();
    virtual void procMove();
    virtual void procConstraint();
    virtual void procFixPos();
    virtual void procObjCollReact();

    Weapon& obj() const;
    Weapon& obj();
    Weapon* objPtr();

private:
    Weapon& mObj;
};

}
}
}

#endif
