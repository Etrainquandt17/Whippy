#include "scn/step/weapon/crackershot/StateMain.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "mcoll/LandManager.h"
#include "ocoll/Attack.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/core/PermEffect.h"
#include "scn/step/map/LandManager.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Weapon.h"

namespace scn {
namespace step {
namespace weapon {
namespace crackershot {

StateMain::StateMain(Weapon* weapon)
    : StateBase(weapon), _8(0), _C(false), _10(10), _14(weapon->variation() == 1 ? 0 : 90), _18(0.0f) {
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x249));
    obj().objColl().addAttack(0, 0.5f);
    obj().objColl().setAttackTypeSub(static_cast<ocoll::AttackType>(0x24A));
    obj().objColl().addAttackSub(0, 0.25f);
}

StateMain::~StateMain() {}

void StateMain::procAnim() {
    if (_C) {
        if (_10 != 0) {
            _10--;
        } else {
            obj().dead();
        }
    } else {
        _8++;
        if (_8 >= _14) {
            mfExplode();
        } else if (_8 == 1) {
            obj().effect().normal().requestN(static_cast<effect::Kind>(0x33B), 0);
        }
    }
}

void StateMain::procMove() {
    if (!_C) {
        const gobj::MoveParamDecel& decel = gobj::MoveParamDecel::Create(0.001f);
        const gobj::MoveParamFall& fall = gobj::MoveParamFall::Create(0.5f, 0.02f, 0.005f);
        obj().move().airDecelFall(decel, fall);
    }
}

void StateMain::procFixPos() {
    if (!_C) {
        if (obj().comp().mapLandManager().native().isWaterGrid(obj().location().pos().getXY())) {
            mfExplode();
        }
    }
}

void StateMain::procObjCollReact() {
    if (obj().objColl().attack().isCollide() || obj().objColl().attack().isCollideGimmick() || obj().mapColl().isHit()) {
        mfExplode();
    }
}

void StateMain::mfExplode() {
    if (!_C) {
        _C = true;
        obj().move().resetVelocity();
        obj().mapColl().setValid(false);
        obj().comp().permEffect().normal().requestP(static_cast<effect::Kind>(0x339), obj().location().pos());
        obj().objColl().clearAttack();
        obj().objColl().setAttackCenter(0, obj().location().pos().getXY());
        obj().objColl().addAttack(0, 1.5f);
        obj().objColl().addAttackSub(0, 0.5f);
        obj().model().setVisibility(false);
    }
}

}}}}  // namespace scn::step::weapon::crackershot
