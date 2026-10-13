#include "scn/step/weapon/spearspear/StateStickObj.h"

#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/spearspear/Param.h"
#include "scn/step/weapon/spearspear/Utility.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace weapon {
namespace spearspear {

StateStickObj::StateStickObj(Weapon* weapon, f32 rot) : StateBase(weapon), mAlgorithm(*weapon), mFrame(0), mRot(rot) {
    obj().objColl().clearAttack();
    obj().model().rotCtrl().setRotV(mRot);
    obj().model().reqScript(2);
    obj().soundSE().start(0x23A);
}

StateStickObj::~StateStickObj() {}

void StateStickObj::procAnim() {
    obj().model().rotCtrl().setRotV(mRot);
    if (++mFrame == obj().param().spearSpear()._20) {
        Utility::Vanish(obj());
    } else if (mFrame >= obj().param().spearSpear()._24) {
        obj().dead();
    }
}

void StateStickObj::procMove() {
    mAlgorithm.procMove();
}

}}}}  // namespace scn::step::weapon::spearspear
