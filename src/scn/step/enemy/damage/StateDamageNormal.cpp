#include "scn/step/enemy/damage/StateDamageNormal.h"

#include "gobj/Anim.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "ocoll/Hit.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/DamageInfo.h"
#include "scn/step/chara/HitPoint.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/Water.h"
#include "scn/step/enemy/CharaParam.h"
#include "scn/step/enemy/DamageFlash.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/damage/Utility.h"

namespace scn {
namespace step {
namespace enemy {
namespace damage {

StateDamageNormal::StateDamageNormal(Enemy* enemy) : StateBase(enemy), mFrame(0), mEndFrame(30), mIsDeadNoItem(false) {
    Utility::OnDamageStart(&obj());
    obj().model().reqScript(5);
    Utility::EmDamageUtility_InitTarget(&obj());
    Utility::EmDamageUtility_InitVelocity(&obj());
    if (obj().move().velocity().x != 0.0f && !obj().charaParam()._45) {
        bool isLeft = obj().move().velocity().x < 0.0f;
        obj().target().setIsRightDir(isLeft);
    }
    ocoll::Element element = ocoll::ELEMENT_0;
    if (obj().objColl().bodyColl().hit().isCollide()) {
        element = static_cast<ocoll::Element>(obj().damageInfo().data().mElement);
    } else if (obj().mapColl().result().isOnFire()) {
        element = ocoll::ELEMENT_2;
    }
    obj().damageFlash().set(element);
    if (obj().water().isInWater()) {
        obj().model().anim().setFrameRate(0.6f);
        mEndFrame = 40;
    }
    if (obj().damageInfo().isValid() && obj().damageInfo().data().mAttackType == 0x176) {
        mIsDeadNoItem = true;
    }
    if (obj().mapColl().result()._6 || obj().mapColl().result().isOnFire()) {
        mIsDeadNoItem = true;
    }
}

StateDamageNormal::~StateDamageNormal() {
    Utility::OnDamageEnd(&obj());
    obj().move().resetVelocity();
}

void StateDamageNormal::procAnim() {
    mFrame++;
    if (mFrame >= mEndFrame) {
        if (obj().hitPoint().isDead()) {
            if (mIsDeadNoItem) {
                if (obj().isSuper()) {
                    obj().deadWithEffect();
                } else {
                    obj().deadWithEffectNoItem();
                }
            } else {
                obj().deadWithEffect();
            }
        } else {
            obj().recover();
        }
    }
}

void StateDamageNormal::procMove() {
    Utility::EmDamageUtility_Move(&obj());
}

void StateDamageNormal::procFixPos() {
    Utility::EmDamageUtility_ReflectWall(&obj());
}

}
}
}
}
