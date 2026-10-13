#ifndef SCN_STEP_HERO_FIRE_STATEFIREIGNITION_H
#define SCN_STEP_HERO_FIRE_STATEFIREIGNITION_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace fire {

class StateFireIgnition : public StateBase {
public:
    StateFireIgnition(Hero* hero);
    virtual ~StateFireIgnition();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    int mFrame;
};

}}}}  // namespace scn::step::hero::fire

#endif
