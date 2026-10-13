#ifndef SCN_STEP_HERO_NEEDLE_STATEDASHEND_H
#define SCN_STEP_HERO_NEEDLE_STATEDASHEND_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace needle {

class StateDashEnd : public StateBase {
public:
    StateDashEnd(Hero* hero);
    virtual ~StateDashEnd();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    bool mIsRight;
};

}}}}  // namespace scn::step::hero::needle

#endif
