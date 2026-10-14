#include "scn/step/enemy/liepa/StateFlyAttack.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/common/StateShootingFly.h"
#include "scn/step/enemy/liepa/Custom.h"
#include "scn/step/enemy/liepa/ParamData.h"
#include "snd/SERequestor.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace liepa {

StateFlyAttack::StateFlyAttack(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().model().reqScript(7);
}

StateFlyAttack::~StateFlyAttack() {}

void StateFlyAttack::procAnim() {
    const ParamData& param = obj().param().liepa();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    mFrame++;
    if (mFrame == param.mShotFrame) {
        custom.reqShot();
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<common::StateShootingFly, Enemy*>(objPtr());
    }
}

void StateFlyAttack::procMove() {
    const ParamData& param = obj().param().liepa();
    obj().move().decel(param.mDecel);
}

void StateFlyAttack::procFixPos() {}

}}}}  // namespace scn::step::enemy::liepa
