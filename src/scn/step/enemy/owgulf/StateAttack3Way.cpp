#include "scn/step/enemy/owgulf/StateAttack3Way.h"

#include "g3d/NodeAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/NodeRepos.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
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
#include "scn/step/enemy/owgulf/Custom.h"
#include "scn/step/enemy/owgulf/ParamData.h"
#include "snd/SERequestor.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace owgulf {

StateAttack3Way::StateAttack3Way(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().footState().setAir();
    obj().model().reqScript(9);
    effect::Kind kind = obj().target().isRightDir() ? static_cast<effect::Kind>(0x5a1) : static_cast<effect::Kind>(0x5a0);
    obj().effect().state().requestP(kind, obj().model().model().nodes().at(1).worldMtx().getT());
}

void StateAttack3Way::procAnim() {
    const ParamData& param = obj().param().owgulf();
    mFrame++;
    if (mFrame == param.m3WayFrame) {
        shot(param.m3WayAngle[0]);
        shot(param.m3WayAngle[1]);
        shot(param.m3WayAngle[2]);
    }
    if (obj().model().isAllEnd()) {
        obj().brainCtrl().toValid();
    }
}

void StateAttack3Way::shot(f32 angle) {
    f32 sin = Math::SinDegF(angle);
    f32 cos = Math::CosDegF(angle);
    DynamicCastToRef<Custom, ICustom>(obj().custom()).shot(obj().location().pos() + Vector3(0.0f, 0.5f, 0.0f), Vector3(cos * obj().target().getSign(), -sin, 0.0f) * obj().param().owgulf().m3WaySpeed,
        static_cast<weapon::owgulffeather::VariationKind>(1));
}

}}}}  // namespace scn::step::enemy::owgulf
