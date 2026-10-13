#ifndef SCN_STEP_HERO_FIRE_STATEFIREBREATHEND_H
#define SCN_STEP_HERO_FIRE_STATEFIREBREATHEND_H

#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace fire {

class StateFireBreathEnd : public StateBase {
public:
    StateFireBreathEnd(Hero* hero);
    virtual ~StateFireBreathEnd();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::hero::fire

#endif
