#include "scn/step/enemy/waddledee/StateSmashed.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/ObjCollReact.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/damage/Utility.h"
#include "scn/step/enemy/waddledee/ParamData.h"

namespace scn {
namespace step {
namespace enemy {
namespace waddledee {

StateSmashed::StateSmashed(Enemy* enemy) : StateBase(enemy), _8(0), mRotH(0.0f), mIsLanded(false) {
    obj().footState().setAir();
    obj().nururi().setValid(false);
    obj().model().reqScript(6);
    if (obj().kind() != 0x8B) {
        damage::Utility::EmDamageUtility_InitTarget(&obj());
    }
    obj().objColl().bodyColl().setStateXlu();
    obj().objCollReact().setDamageState();
}

StateSmashed::~StateSmashed() {
    obj().model().rotCtrl().initRotV(0.0f);
    obj().model().rotCtrl().initRotH(0.0f);
    obj().nururi().setValid(true);
}

// TODO: procAnim (turns the model along the velocity; needs hel::math::Vector2's inline length and normalize) and
// procFixPos (works on a copy of gobj::Move, 0x14 bytes, whose members the shared header does not have).

void StateSmashed::procMove() {
    obj().move().airDecelFall(obj().param().waddledee().mSmashedDecel, obj().param().waddledee().mSmashedFall);
}

}
}
}
}
