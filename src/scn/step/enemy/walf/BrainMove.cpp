#include "scn/step/enemy/walf/BrainMove.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/walf/Custom.h"
#include "scn/step/enemy/walf/StateMoveInWater.h"
#include "scn/step/enemy/walf/StateMoveOnGround.h"
#include "scn/step/enemy/walf/StateMoveOnWater.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace walf {

BrainMove::BrainMove(Enemy& enemy) : BrainBase(enemy) {}

bool BrainMove::onStart() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (custom.isInWater()) {
        obj().stateChanger().setNextState<StateMoveInWater, Enemy*>(&obj());
    } else if (custom.isFloating()) {
        obj().stateChanger().setNextState<StateMoveOnWater, Enemy*>(&obj());
    } else {
        obj().stateChanger().setNextState<StateMoveOnGround, Enemy*>(&obj());
    }
    return true;
}

bool BrainMove::onRecover() {
    if (DynamicCastToRef<Custom, ICustom>(obj().custom()).isInWater()) {
        obj().stateChanger().setNextState<StateMoveInWater, Enemy*>(&obj());
    } else {
        obj().stateChanger().setNextState<StateMoveOnGround, Enemy*>(&obj());
    }
    return true;
}

}}}}  // namespace scn::step::enemy::walf
