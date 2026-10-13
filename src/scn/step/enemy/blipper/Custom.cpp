#include "scn/step/enemy/blipper/Custom.h"

#include "gobj/Move.h"
#include "hel/math/Vector2.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/DamageInfo.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/ocoll/Element.h"
#include "scn/step/enemy/CharaParam.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/blipper/StateChase.h"
#include "scn/step/enemy/blipper/StateDive.h"
#include "scn/step/enemy/blipper/StateFall.h"
#include "scn/step/enemy/blipper/StateFlyingOut.h"
#include "scn/step/enemy/blipper/StateMove.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace blipper {

Custom::Custom(Enemy& enemy) : CustomBase(enemy) {}

bool Custom::onInit() {
    obj().objColl().clearBodyColl();
    if (obj().variation() == 0x170) {
        obj().objColl().bodyColl().initAttackType(static_cast<ocoll::AttackType>(0x1e7));
    }
    f32 scale = Utility::GetModelScaleBySizeType(obj());
    obj().objColl().addBodyColl(1, 0.55f * scale);
    obj().nururi().changeSetting(hel::math::Vector2(0.0f, 0.0f), 2.0f * obj().charaParam()._2c, 2.0f * obj().charaParam()._2c,
                                 nururi::MODE_1);
    return false;
}

bool Custom::onInWater() {
    obj().soundSE().start(0x2f6);
    switch (obj().variation()) {
    case 0x3a:
        obj().stateChanger().setNextState<StateChase, Enemy*>(&obj());
        break;
    case 0x3b:
        obj().stateChanger().setNextState<StateDive, Enemy*>(&obj());
        break;
    default:
        obj().stateChanger().setNextState<StateMove, Enemy*>(&obj());
        break;
    }
    return true;
}

bool Custom::onOutWater() {
    obj().soundSE().start(0x2f6);
    obj().move().setSpeedV(0.1f);
    if (obj().variation() == 0x3b) {
        obj().stateChanger().setNextState<StateFlyingOut, Enemy*>(&obj());
    } else {
        obj().stateChanger().setNextState<StateFall, Enemy*>(&obj());
    }
    return true;
}

bool Custom::onHitPointIsZero() {
    if (obj().damageInfo().data().mAttackType == 0x12) {
        return false;
    }
    if (obj().damageInfo().element() == ocoll::ELEMENT_3) {
        obj().model().rotCtrl().resetRot();
        obj().model().unsetCustomMtx();
    }
    return false;
}

void Custom::onCaptured() {
    obj().model().rotCtrl().resetRot();
    obj().model().unsetCustomMtx();
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

}}}}  // namespace scn::step::enemy::blipper
