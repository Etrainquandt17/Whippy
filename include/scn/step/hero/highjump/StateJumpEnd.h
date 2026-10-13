#ifndef SCN_STEP_HERO_HIGHJUMP_STATEJUMPEND_H
#define SCN_STEP_HERO_HIGHJUMP_STATEJUMPEND_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace highjump {

class StateJumpEnd : public StateBase {
public:
    StateJumpEnd(Hero* hero);
    virtual ~StateJumpEnd();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 _8;
};

}}}}  // namespace scn::step::hero::highjump

#endif
