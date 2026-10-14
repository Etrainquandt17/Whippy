#include "scn/step/enemy/lupa/StateWait.h"

#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/lupa/Custom.h"
#include "scn/step/enemy/lupa/ParamData.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace lupa {

StateWait::StateWait(Enemy* enemy) : StateBase(enemy) {
    obj().model().reqScript(0);
    obj().brainCtrl().toValid();
}

StateWait::~StateWait() {}

void StateWait::procAnim() {
    Utility::TurnHero(obj());
}

void StateWait::procMove() {
    const ParamData& param = obj().param().lupa();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().move().decel(param.mWaitDecel);
    custom.approachMap();
}

void StateWait::procFixPos() {}

}}}}  // namespace scn::step::enemy::lupa
