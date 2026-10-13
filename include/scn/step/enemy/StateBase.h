#ifndef SCN_STEP_ENEMY_STATEBASE_H
#define SCN_STEP_ENEMY_STATEBASE_H

#include "scn/step/enemy/IState.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

// TODO: the functions are IState's, which does not declare them yet.
class StateBase : public IState {
public:
    StateBase(Enemy* enemy);
    virtual ~StateBase();
    virtual void procAnim();
    virtual void procMove();
    virtual void procConstraint();
    virtual void procFixPos();
    virtual void procObjCollReact();

    Enemy& obj() const;
    Enemy& obj();
    Enemy* objPtr();

private:
    Enemy& mObj;
};

}}}  // namespace scn::step::enemy

#endif
