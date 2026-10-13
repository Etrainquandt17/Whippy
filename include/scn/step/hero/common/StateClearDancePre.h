#ifndef SCN_STEP_HERO_COMMON_STATECLEARDANCEPRE_H
#define SCN_STEP_HERO_COMMON_STATECLEARDANCEPRE_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

class StateClearDancePre : public StateBase {
public:
    StateClearDancePre(Hero* hero, u32 zoom);
    virtual ~StateClearDancePre();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    u32 mZoom;
};

}}}}  // namespace scn::step::hero::common

#endif
