#include "scn/step/enemy/waddledee/StateGrandLowperAppear.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "mintglue/VectorInline.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/waddledee/ParamData.h"
#include "scn/step/enemy/waddledee/StateGrandLowperLanding.h"

namespace scn {
namespace step {
namespace enemy {
namespace waddledee {

StateGrandLowperAppear::StateGrandLowperAppear(Enemy* enemy)
    : StateBase(enemy), mAlgorithm(*enemy), mRot(0.0f), mRotSpeed(0.0f) {
    const ParamData& param = obj().param().waddledee();
    obj().footState().setAir();
    obj().objColl().setBodyCollStateHitOnly();
    obj().model().reqScript(17);
    obj().move().resetVelocity();
    mRotSpeed = param.mGrandLowperAppearRotSpeed;
}

StateGrandLowperAppear::~StateGrandLowperAppear() {
    obj().objColl().bodyColl().setStateNormal();
    obj().model().unsetCustomMtx();
}

void StateGrandLowperAppear::procAnim() {
    const ParamData& param = obj().param().waddledee();
    mAlgorithm.procAnim();
    mRot += mRotSpeed;
    if (mRot >= 360.0f) {
        mRot -= 360.0f;
    }
    mRotSpeed -= param.mGrandLowperAppearRotDecel;
    if (mRotSpeed < 0.0f) {
        mRotSpeed = 0.0f;
    }
    hel::math::Vector3 rot(mRot, 0.0f, 0.0f);
    Utility::SetCustomMtxRotate(obj(), rot);
}

void StateGrandLowperAppear::procMove() {
    mAlgorithm.procMove();
}

void StateGrandLowperAppear::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().stateChanger().setNextState<StateGrandLowperLanding, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::waddledee
