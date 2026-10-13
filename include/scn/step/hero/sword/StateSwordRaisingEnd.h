#ifndef SCN_STEP_HERO_SWORD_STATESWORDRAISINGEND_H
#define SCN_STEP_HERO_SWORD_STATESWORDRAISINGEND_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace sword {

class StateSwordRaisingEnd : public StateBase {
public:
    StateSwordRaisingEnd(Hero* hero);
    virtual ~StateSwordRaisingEnd();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 _8;
};

}}}}  // namespace scn::step::hero::sword

#endif
