#ifndef SCN_STEP_ITEM_STATE_STATEVACUUMRECEIVE_H
#define SCN_STEP_ITEM_STATE_STATEVACUUMRECEIVE_H

#include "scn/step/chara/MoveAlgorithmVacuumReceive.h"
#include "scn/step/item/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace item {
namespace state {

class StateVacuumReceive : public StateBase {
public:
    StateVacuumReceive(Item* item, u32 time);
    virtual ~StateVacuumReceive();

    virtual void procAnim();
    virtual void procFixPos();

private:
    chara::MoveAlgorithmVacuumReceive mMoveAlgorithm;
};

}}}}  // namespace scn::step::item::state

#endif
