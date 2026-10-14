#include "scn/step/enemy/parasoldoo/BrainRelease.h"

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
#include "scn/step/enemy/parasoldoo/Custom.h"
#include "scn/step/enemy/parasoldoo/StateFall.h"
#include "scn/step/enemy/parasoldoo/StateParasolFall.h"
#include "snd/SERequestor.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace parasoldoo {

BrainRelease::BrainRelease(Enemy& enemy) : BrainBase(enemy) {}

bool BrainRelease::onStart() {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).setReleaseOnLanding();
    obj().stateChanger().setNextState<StateParasolFall, Enemy*>(&obj());
    return true;
}

bool BrainRelease::onRecover() {
    obj().stateChanger().setNextState<StateFall, Enemy*>(&obj());
    return true;
}

void BrainRelease::update() {
    Utility::ChkNururiTurn(obj());
}

}}}}  // namespace scn::step::enemy::parasoldoo
