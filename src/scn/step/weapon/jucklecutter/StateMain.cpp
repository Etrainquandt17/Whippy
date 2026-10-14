#include "scn/step/weapon/jucklecutter/StateMain.h"

#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector3.h"
#include "ocoll/Attack.h"
#include "ocoll/Hit.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/core/PermEffect.h"
#include "scn/step/core/PermSoundSE.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/jucklecutter/Param.h"
#include "snd/SERequestor.h"

using hel::math::Matrix34;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace weapon {
namespace jucklecutter {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), _8(0), _C(0.0f) {
    const Param& param = obj().param().juckleCutter();
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x19F));
    obj().objColl().addAttack(1, param._0);
    obj().objColl().addHit(1, param._4);
    const mcoll::detail::ShapeDiamondContext& shape = mcoll::detail::ShapeDiamondContext::CreateBaseBottom(param._10, param._10, param._10);
    obj().mapColl().changeActorShape(shape);
    obj().soundSE().start(0x29C);
    obj().effect().normal().requestN(static_cast<effect::Kind>(0xCE), 2);
}

void StateMain::procAnim() {
    _C += obj().param().juckleCutter()._8;
    Matrix34 mtx = Matrix34::CreateRotAxisDeg(Vector3::BASIS_X, _C);
    obj().model().model().nodes().at(2).localMtx().setRTMtx(mtx);
}

void StateMain::procMove() {
    obj().move().airAccelFall(!obj().target().isRightDir(), gobj::MoveParamAccel::Zero(), gobj::MoveParamFall::Zero());
}

void StateMain::procFixPos() {
    if (++_8 == 250 || obj().mapColl().isHit() || obj().objColl().attack().isCollide() || obj().objColl().attack().isCollideGimmick() ||
        obj().objColl().hit().isCollide()) {
        Vector3 pos = obj().location().pos();
        pos.y += 0.5f;
        obj().comp().permEffect().normal().requestP(static_cast<effect::Kind>(0xCF), pos);
        obj().soundSE().stop();
        obj().comp().permSoundSE().start(0x2FC);
        obj().dead();
    }
}

}}}}  // namespace scn::step::weapon::jucklecutter
