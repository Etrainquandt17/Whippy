#ifndef SCN_STEP_HERO_DAMAGE_STATEGUARD_H
#define SCN_STEP_HERO_DAMAGE_STATEGUARD_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace damage {

class StateGuard : public StateBase {
public:
    StateGuard(Hero* hero);
    virtual ~StateGuard();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
};

}}}}  // namespace scn::step::hero::damage

#endif
