#include "scn/step/enemy/metalgeneralbomb/StateLanding.h"

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
#include "scn/step/enemy/metalgeneralbomb/Custom.h"
#include "scn/step/enemy/metalgeneralbomb/ParamData.h"
#include "snd/SERequestor.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace metalgeneralbomb {

StateLanding::StateLanding(Enemy* enemy, bool isFloor) : StateBase(enemy), mFrame(0), mIsFloor(isFloor) {
    obj().footState().setAir();
    obj().model().reqScript(0);
    obj().move().resetVelocity();
}

StateLanding::~StateLanding() {}

void StateLanding::procAnim() {
    const ParamData& param = obj().param().metalgeneralbomb();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    mFrame++;
    if (mFrame == param.mBlinkFrame) {
        obj().model().reqScript(7);
    }
    if (mIsFloor) {
        obj().model().rotCtrl().initRotV(0.0f);
    } else {
        obj().model().rotCtrl().initRotV(90.0f * obj().target().getSign());
    }
    if (mFrame == param.mExplodeFrame) {
        custom.reqRollExp(true);
        obj().dead();
    }
}

void StateLanding::procMove() {}

void StateLanding::procFixPos() {}

}}}}  // namespace scn::step::enemy::metalgeneralbomb
