#include "scn/step/enemy/glunk/StateDamageNoSmash.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "ocoll/Hit.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/DamageInfo.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/Water.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/DamageFlash.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/damage/Utility.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace glunk {

StateDamageNoSmash::StateDamageNoSmash(Enemy* enemy) : StateBase(enemy), mFrame(0), mEndFrame(30) {
    damage::Utility::OnDamageStart(&obj());
    obj().model().reqScript(5);
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
}

StateDamageNoSmash::~StateDamageNoSmash() {
    damage::Utility::OnDamageEnd(&obj());
}

void StateDamageNoSmash::procAnim() {
    if (++mFrame >= mEndFrame) {
        obj().recover();
    }
}

}
}
}
}
