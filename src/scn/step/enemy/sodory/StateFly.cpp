#include "scn/step/enemy/sodory/StateFly.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "mcoll/detail/ShapeDiamondContext.h"
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
#include "scn/step/enemy/sodory/ParamData.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace sodory {

StateFly::StateFly(Enemy* enemy) : StateBase(enemy), mFrame(0), _c(0.0f) {
    obj().footState().setAir();
    if (obj().model().anim().currentG3DAnimIndex() != 6) {
        obj().model().reqScript(4);
    }
    obj().model().anim().setFrameRate(1.0f);
    obj().target().setIsRightDir(false);
    obj().mapColl().changeActorShape(mcoll::detail::ShapeDiamondContext::CreateBaseBottom(
        obj().param().sodory().mFlyShapeSize, obj().param().sodory().mFlyShapeSize, obj().param().sodory().mFlyShapeSize));
}

StateFly::~StateFly() {}

void StateFly::procAnim() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (mFrame < custom.getFrame()) {
        mFrame++;
        if (mFrame >= custom.getFrame()) {
            obj().brainCtrl().toValid();
        }
    }
}

void StateFly::procMove() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.addOffsY();
    custom.setPosYR(0.0f);
}

void StateFly::procFixPos() {
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).setDirectionAll();
}

}}}}  // namespace scn::step::enemy::sodory
