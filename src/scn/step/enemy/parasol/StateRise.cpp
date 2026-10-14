#include "scn/step/enemy/parasol/StateRise.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "mcoll/detail/ShapeDiamondContext.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/core/PermEffect.h"
#include "scn/step/core/PermSoundSE.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/parasol/ParamData.h"
#include "snd/SERequestor.h"

using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace parasol {

StateRise::StateRise(Enemy* enemy) : StateBase(enemy), mSpeedV(0.0f), mRot(0.0f) {
    obj().footState().setAir();
    obj().mapColl().setValid(true);
    obj().mapColl().changeActorShape(mcoll::detail::ShapeDiamondContext::CreateBaseBottom(0.4f, 1.09f, 0.59f));
    obj().nururi().setCanNururi(false);
    obj().nururi().setValid(false);
    obj().model().reqScript(0);
    obj().model().anim().setFrame(58.0f);
    obj().model().anim().setFrameRate(0.0f);
}

void StateRise::procAnim() {
    mRot += 5.0f * obj().target().getSign();
    if (mRot >= 360.0f) {
        mRot -= 360.0f;
    }
    if (mRot < 0.0f) {
        mRot += 360.0f;
    }
    obj().model().rotCtrl().setRotH(mRot);
}

void StateRise::procMove() {
    const ParamData& param = obj().param().parasol();
    mSpeedV += 0.0007f;
    obj().move().setSpeedV(mSpeedV);
    obj().move().airAccelFall(!obj().target().isRightDir(), param.mAccel, param.mFall);
}

void StateRise::procFixPos() {
    if (obj().mapColl().result().isHit()) {
        Vector3 pos = obj().location().pos();
        pos.y += 1.5f;
        obj().comp().permEffect().normal().requestP(static_cast<effect::Kind>(0x127), pos);
        obj().soundSE().start(0x2a5);
        obj().dead();
    }
}

}}}}  // namespace scn::step::enemy::parasol
