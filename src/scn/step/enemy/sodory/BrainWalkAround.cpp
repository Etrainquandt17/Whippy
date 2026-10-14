#include "scn/step/enemy/sodory/BrainWalkAround.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/CliffChecker.h"
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
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/sodory/Custom.h"
#include "scn/step/enemy/sodory/StateWalkAround.h"
#include "snd/SERequestor.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace sodory {

BrainWalkAround::BrainWalkAround(Enemy& enemy) : BrainBase(enemy) {}

bool BrainWalkAround::onStart() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.resetBasePosX();
    custom.setDirectionAll();
    obj().stateChanger().setNextState<StateWalkAround, Enemy*>(&obj());
    return true;
}

bool BrainWalkAround::onLanding() {
    return onStart();
}

bool BrainWalkAround::onRecover() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.resetBasePosX();
    custom.setDirectionAll();
    custom.setFrame();
    return false;
}

}}}}  // namespace scn::step::enemy::sodory
