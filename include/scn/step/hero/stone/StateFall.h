#ifndef SCN_STEP_HERO_STONE_STATEFALL_H
#define SCN_STEP_HERO_STONE_STATEFALL_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace stone {

class Context;

class StateFall : public StateBase {
public:
    StateFall(Hero* hero, Context& context);
    virtual ~StateFall();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual bool procObjCollReact();

private:
    Context& mContext;
    u32 mFrame;
};

}}}}  // namespace scn::step::hero::stone

#endif
