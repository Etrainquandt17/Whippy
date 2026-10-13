#include "scn/step/enemy/damage/StateDamageWingToss.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "ocoll/Hit.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/DamageInfo.h"
#include "scn/step/chara/HitPoint.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/enemy/DamageFlash.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/ObjCollReact.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/common/ParamData.h"
#include "scn/step/enemy/damage/Utility.h"

namespace scn {
namespace step {
namespace enemy {
namespace damage {

StateDamageWingToss::StateDamageWingToss(Enemy* enemy) : StateBase(enemy), mIsBound(false), mFrame(0), mCollFrame(30) {
    Utility::OnDamageStart(&obj());
    obj().model().reqScript(6);
    Utility::EmDamageUtility_InitTarget(&obj());
    Utility::EmDamageUtility_InitVelocity(&obj());
    ocoll::Element element = static_cast<ocoll::Element>(13);
    if (obj().objColl().bodyColl().hit().isCollide()) {
        element = static_cast<ocoll::Element>(obj().damageInfo().data().mElement);
    } else if (obj().mapColl().result().isOnFire()) {
        element = ocoll::ELEMENT_2;
    }
    obj().damageFlash().set(element);
}

StateDamageWingToss::~StateDamageWingToss() {
    Utility::OnDamageEnd(&obj());
    obj().move().resetVelocity();
}

void StateDamageWingToss::procAnim() {
    if (mCollFrame != 0 && --mCollFrame == 0 && !obj().hitPoint().isDead()) {
        switch (obj().kind()) {
        case 0x5c:
            obj().objColl().bodyColl().setStateHitOnly();
            break;
        case 0x64:
            obj().objColl().bodyColl().setStateCaptureOnly();
            break;
        default:
            obj().objColl().bodyColl().setStateNormal();
            break;
        }
        obj().objCollReact().resetState();
    }
    mFrame++;
    if (mIsBound) {
        if (mFrame >= 40) {
            recover();
        }
    } else if (mFrame >= 100) {
        recover();
    }
}

void StateDamageWingToss::procMove() {
    Utility::UpdateMoveRate(&obj());
    obj().move().airDecelFall(gobj::MoveParamDecel::Zero(), obj().param().common().mFall);
}

void StateDamageWingToss::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor && obj().move().velocity().y < 0.0f) {
        if (!mIsBound) {
            mIsBound = true;
            mFrame = 0;
            obj().footState().setAir();
            f32 speed = obj().move().velocity().y;
            speed *= -0.75f;
            obj().move().setSpeedV(speed);
        } else {
            obj().move().resetSpeedV();
            recover();
        }
    }
}

void StateDamageWingToss::recover() {
    if (obj().hitPoint().isDead()) {
        obj().deadWithEffect();
    } else {
        obj().recover();
    }
}

}
}
}
}
