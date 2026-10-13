#ifndef SCN_STEP_HERO_DAMAGE_STATESPINE_H
#define SCN_STEP_HERO_DAMAGE_STATESPINE_H

#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace damage {

class StateSpine : public StateBase {
public:
    StateSpine(Hero* hero);
    virtual ~StateSpine();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::hero::damage

#endif
