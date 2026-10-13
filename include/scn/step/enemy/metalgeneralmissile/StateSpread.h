#ifndef SCN_STEP_ENEMY_METALGENERALMISSILE_STATESPREAD_H
#define SCN_STEP_ENEMY_METALGENERALMISSILE_STATESPREAD_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace metalgeneralmissile {

// TODO: members unknown; only the interface that boss::hrd3pilot and boss::metalgeneral use.
class StateSpread : public StateBase {
public:
    enum SpreadKind {
        SPREAD_KIND_0,
        SPREAD_KIND_1,
        SPREAD_KIND_2
    };

    StateSpread(Enemy* enemy, SpreadKind kind);
    virtual ~StateSpread();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::enemy::metalgeneralmissile

#endif
