#ifndef SCN_STEP_HERO_STATEBASE_H
#define SCN_STEP_HERO_STATEBASE_H

#include "scn/step/hero/IState.h"

namespace scn {
namespace step {
namespace hero {

class Hero;

// TODO: the functions are IState's, which does not declare them yet.
class StateBase : public IState {
public:
    StateBase(Hero* hero);
    virtual ~StateBase();
    virtual void procAnim();
    virtual void procMove();
    virtual void procConstraint();
    virtual void procFixPos();
    virtual bool procObjCollReact();
    virtual void procEnd();

    Hero& obj() const;
    Hero& obj();
    Hero* objPtr();

private:
    Hero& mObj;
};

}}}  // namespace scn::step::hero

#endif
