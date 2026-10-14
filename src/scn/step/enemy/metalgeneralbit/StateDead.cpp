#include "scn/step/enemy/metalgeneralbit/StateDead.h"

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
#include "scn/step/chara/Shake.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/metalgeneralbit/Custom.h"
#include "scn/step/enemy/metalgeneralbit/ParamData.h"
#include "snd/SERequestor.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace metalgeneralbit {

StateDead::StateDead(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().footState().setAir();
    obj().soundSE().start(0x3f3);
}

StateDead::~StateDead() {}

void StateDead::procAnim() {
    const ParamData& param = obj().param().metalgeneralbit();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    mFrame++;
    if (mFrame == param.mDeadFrame) {
        custom.reqRollExp();
        obj().dead();
    } else if (mFrame % 5 == 0) {
        obj().model().shake().request(static_cast<chara::ShakeKind>(1));
    }
}

void StateDead::procMove() {}

void StateDead::procFixPos() {}

}}}}  // namespace scn::step::enemy::metalgeneralbit
