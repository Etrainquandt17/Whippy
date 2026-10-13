#ifndef SCN_STEP_BOSS_DOUBTER_STATEJUGGLINGATTACK_H
#define SCN_STEP_BOSS_DOUBTER_STATEJUGGLINGATTACK_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace doubter {

class StateJugglingAttack : public StateBase {
public:
    enum JugglingShotKind {
        JugglingShotKind_Normal,
        JugglingShotKind_Fast,
        JugglingShotKind_Search,
    };

    StateJugglingAttack(Boss* boss, JugglingShotKind kind);
    virtual ~StateJugglingAttack();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    bool mIsFirst;
    JugglingShotKind mKind;
};

}}}}  // namespace scn::step::boss::doubter

#endif
