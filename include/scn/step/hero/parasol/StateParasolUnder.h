#ifndef SCN_STEP_HERO_PARASOL_STATEPARASOLUNDER_H
#define SCN_STEP_HERO_PARASOL_STATEPARASOLUNDER_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace parasol {

class StateParasolUnder : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateParasolUnder(Hero* hero);
    virtual ~StateParasolUnder();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
};

}}}}  // namespace scn::step::hero::parasol

#endif
