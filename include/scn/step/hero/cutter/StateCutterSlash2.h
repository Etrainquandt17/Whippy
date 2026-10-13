#ifndef SCN_STEP_HERO_CUTTER_STATECUTTERSLASH2_H
#define SCN_STEP_HERO_CUTTER_STATECUTTERSLASH2_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace cutter {

class StateCutterSlash2 : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateCutterSlash2(Hero* hero);
    virtual ~StateCutterSlash2();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual bool procObjCollReact();

private:
    u32 mFrame;
    bool mIsNext;
    bool mIsCheckHit;
};

}}}}  // namespace scn::step::hero::cutter

#endif
