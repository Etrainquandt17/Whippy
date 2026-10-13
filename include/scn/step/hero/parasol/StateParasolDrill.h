#ifndef SCN_STEP_HERO_PARASOL_STATEPARASOLDRILL_H
#define SCN_STEP_HERO_PARASOL_STATEPARASOLDRILL_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace parasol {

class StateParasolDrill : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateParasolDrill(Hero* hero);
    virtual ~StateParasolDrill();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    bool _C;
    f32 _10;
    bool _14;
    bool mIsAir;
};

}}}}  // namespace scn::step::hero::parasol

#endif
