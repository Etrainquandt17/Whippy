#include "scn/step/enemy/stareffect/StatePuff.h"

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
#include "scn/step/enemy/CharaParam.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Shadow.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/stareffect/Custom.h"
#include "scn/step/enemy/stareffect/ParamData.h"
#include "snd/SERequestor.h"

using hel::common::DynamicCastToRef;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace stareffect {

StatePuff::StatePuff(Enemy* enemy) : StateBase(enemy) {
    obj().model().setScale(Vector3::ALL_ONE * obj().param().stareffect().mPuffScale);
    obj().model().rotCtrl().initRotH(0.0f);
    obj().objColl().setBodyCollStateCaptureOnly();
    obj().model().updateMtx();
}

StatePuff::~StatePuff() {
    obj().model().resetScale();
    obj().shadow().changeDiameter(obj().charaParam()._34);
    obj().model().rotCtrl().resetRot();
}

void StatePuff::procAnim() {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).procAnim();
}

void StatePuff::procMove() {
    const ParamData& param = obj().param().stareffect();
    obj().move().decel(param.mPuffDecel);
}

}}}}  // namespace scn::step::enemy::stareffect
