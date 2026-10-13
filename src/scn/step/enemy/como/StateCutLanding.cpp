#include "scn/step/enemy/como/StateCutLanding.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "mintglue/VectorInline.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/Shake.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ObjCollReact.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/como/ParamData.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace como {

StateCutLanding::StateCutLanding(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().footState().setGround();
    obj().move().resetVelocity();
    obj().objColl().bodyColl().setStateXlu();
    obj().model().reqScript(2);
    obj().soundSE().start(0x29B);
    obj().model().shake().request(static_cast<chara::ShakeKind>(4));
    obj().objCollReact().setDamageState();
    obj().model().setViewOffset(hel::math::Vector3(0.0f, obj().param().como().mCutLandingViewOffsetY, 0.0f));
    obj().effect().normal().requestP(static_cast<effect::Kind>(0x9F), obj().location().pos());
}

StateCutLanding::~StateCutLanding() {}

void StateCutLanding::procAnim() {
    mFrame++;
    if (mFrame == obj().param().como().mCutLandingFrame) {
        obj().deadWithEffect();
    }
}

void StateCutLanding::procMove() {}

void StateCutLanding::procFixPos() {}

}
}
}
}
