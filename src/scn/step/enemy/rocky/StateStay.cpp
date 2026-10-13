#include "scn/step/enemy/rocky/StateStay.h"

#include "app/Random.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/rocky/ParamData.h"
#include "scn/step/enemy/rocky/StateAttack.h"
#include "scn/step/enemy/rocky/StateFall.h"
#include "scn/step/hero/Manager.h"

namespace scn {
namespace step {
namespace enemy {
namespace rocky {

StateStay::StateStay(Enemy* enemy) : StateBase(enemy), mFrame(0), mAttackFrame(0) {
    obj().footState().setGround();
    obj().model().reqScript(0);
    obj().model().anim().setFrameRate(0.0f);
    obj().move().resetSpeedH();
    mFrame = app::Random::Rand(obj().param().rocky().mStayRandFrame) + obj().param().rocky().mStayBaseFrame;
    mAttackFrame = mFrame - obj().param().rocky().mStayAttackWait;
}

StateStay::~StateStay() {}

void StateStay::procAnim() {
    mFrame--;
    if (mFrame <= 0) {
        obj().brainCtrl().toValid();
    } else if (mFrame < mAttackFrame) {
        bool isFound = false;
        bool isRight = obj().target().isRightDir();
        u32 count = obj().comp().heroManager().getPlayerCount();
        for (u32 i = 0; i < count; i++) {
            hel::math::Vector3 diff = obj().comp().heroManager().getPlayerPosByIndex(i) - obj().location().pos();
            f32 x = hel::math::Math::Abs(diff.x);
            if (x < obj().param().rocky().mStayAttackRangeX && diff.y < obj().param().rocky().mStayAttackRangeTop &&
                diff.y > obj().param().rocky().mStayAttackRangeBottom) {
                isFound = true;
                isRight = diff.x >= 0.0f;
                break;
            }
        }
        if (isFound) {
            obj().target().setIsRightDir(isRight);
            obj().stateChanger().setNextState<StateAttack, Enemy*>(objPtr());
        }
    }
}

void StateStay::procFixPos() {
    if (!obj().mapColl().result().mIsHitFloor) {
        obj().model().anim().setFrameRate(1.0f);
        obj().stateChanger().setNextState<StateFall, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::rocky
