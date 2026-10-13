#ifndef SCN_STEP_BOSS_STATEBASE_H
#define SCN_STEP_BOSS_STATEBASE_H

#include "scn/step/boss/IState.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

// TODO: the functions are IState's, which does not declare them yet.
class StateBase : public IState {
public:
    StateBase(Boss* boss);
    virtual ~StateBase();
    virtual void procAnim();
    virtual void procMove();
    virtual void procConstraint();
    virtual void procFixPos();
    virtual void procObjCollReact();

    Boss& obj() const;
    Boss& obj();
    Boss* objPtr();

private:
    Boss& mObj;
};

}
}
}

#endif
