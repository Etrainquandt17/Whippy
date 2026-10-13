#ifndef SCN_STEP_HERO_STONE_STATEWAIT_H
#define SCN_STEP_HERO_STONE_STATEWAIT_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace stone {

class Context;

class StateWait : public StateBase {
public:
    StateWait(Hero* hero, Context& context);
    virtual ~StateWait();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    Context& mContext;
};

}
}
}
}

#endif
