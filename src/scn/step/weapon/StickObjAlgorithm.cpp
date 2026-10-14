#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS

#include "scn/step/weapon/StickObjAlgorithm.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "hel/math/Vector3.h"
#include "ocoll/Attack.h"
#include "ocoll/AttackResult.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Angry.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Manager.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Weapon.h"
#include "util/ObjRefHandle.h"

using hel::math::Vector3;
using util::ObjRefHandle;

namespace scn {
namespace step {
namespace weapon {

StickObjAlgorithm::StickObjAlgorithm(Weapon& weapon) : mObj(weapon) {
    mObj.move().resetVelocity();
    mObj.mapColl().setValid(false);
    mObj.objColl().clearAttack();
    if (mObj.objColl().attack().result().isCollide()) {
        u64 uid = mObj.objColl().attack().result().getData(0).mOwnerID;
        ObjRefHandle<boss::Boss> boss = mObj.comp().bossManager().getBossByObjCollOwnerID(uid);
        if (boss.isAlive() && boss->kind() == 1 && boss->angry().isAngry()) {
            Vector3 pos = mObj.location().pos();
            pos.z = -2.0f;
            mObj.location().setPos(pos);
        }
    }
}

StickObjAlgorithm::~StickObjAlgorithm() {}

void StickObjAlgorithm::procMove() {
    mObj.move().decel(gobj::MoveParamDecel::Zero());
}

void StickObjAlgorithm::setOffset(const Vector3& offset) {
    Vector3 pos = mObj.location().pos();
    pos += offset;
    mObj.location().setPos(pos);
}

}}}  // namespace scn::step::weapon
