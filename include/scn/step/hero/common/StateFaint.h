#ifndef SCN_STEP_HERO_COMMON_STATEFAINT_H
#define SCN_STEP_HERO_COMMON_STATEFAINT_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

class StateFaint : public StateBase {
public:
    StateFaint(Hero* hero, u32 frame, bool isPauseDisable = false);
    virtual ~StateFaint();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    bool mIsPauseDisable;
};

}}}}  // namespace scn::step::hero::common

#endif
