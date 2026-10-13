#ifndef SCN_STEP_HERO_HAMMER_STATETRIPLEATTACK_H
#define SCN_STEP_HERO_HAMMER_STATETRIPLEATTACK_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace hammer {

class StateTripleAttack : public StateBase {
public:
    StateTripleAttack(Hero* hero);
    virtual ~StateTripleAttack();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    bool _8;
};

}
}
}
}

#endif
