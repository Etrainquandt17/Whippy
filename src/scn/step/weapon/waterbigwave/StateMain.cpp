#include "scn/step/weapon/waterbigwave/StateMain.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/NodeRepos.h"
#include "gobj/Target.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Culling.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/MapCollResult.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Manager.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/waterbigwave/Param.h"
#include "util/ObjRefHandle.h"

using g3d::NodeLocalMtxAccessor;
using hel::math::Matrix34;
using hel::math::Vector2;
using hel::math::Vector3;
using util::ObjRefHandle;

namespace scn {
namespace step {
namespace weapon {
namespace waterbigwave {

namespace {

const u32 targetNodes[] = { 3, 4 };

}

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), mPositions(), _74(true), _75(false), mFrame(0), _7C(0), _80(false) {
    const Param& param = obj().param().waterBigWave();
    u32 interval = param._0;
    u32 jointNum = param._4;
    obj().mapColl().setValid(false);
    obj().culling().setValid(false);
    u32 num = interval * jointNum + 1;
    for (u32 i = 0; i < num; i++) {
        mPositions.add(obj().location().pos().getXY());
    }
    calcJoint();
    obj().effect().normal().changeLayer(static_cast<core::DrawLayerKind>(7));
    obj().move().resetVelocity();
    obj().setValidAttackRumble(true);
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x55E), 0);
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x55C), 1);
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x55D), 2);
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x55F), 1);
}

StateMain::~StateMain() {
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x55B), 0);
}

void StateMain::procAnim() {
    const Param& param = obj().param().waterBigWave();
    mFrame++;
    if (mFrame == 1) {
        obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x7F));
        obj().objColl().setAttackCenter(4, Vector2(obj().target().getSign(), 0.0f));
        obj().objColl().addAttack(2, param._8, Vector2(param._C, param._10));
        obj().objColl().addAttack(3, param._14, Vector2(param._18, param._1C));
        obj().objColl().addAttack(4, param._20, Vector2(param._24, param._28));
    }
    if (mFrame > 180) {
        obj().effect().normal().requestP(static_cast<effect::Kind>(0x574), obj().location().pos());
        obj().effect().normal().requestN(static_cast<effect::Kind>(0x55B), 0);
        obj().dead();
    }
}

void StateMain::procMove() {}

void StateMain::procConstraint() {
    {
        ObjRefHandle<hero::Hero> hero = obj().comp().heroManager().searchHeroFromObjCollOwnerID(obj().objColl().owner().rootUid());
        const hero::Hero& owner = *hero.operator->();
        Vector3 heroPos = owner.location().pos();
        Vector3 nodePos = obj().model().model().nodes().at(1).worldTrans();
        Vector3 pos = obj().location().pos();
        obj().location().setPos(heroPos - nodePos + pos);
        obj().model().updateMtx();
    }
    mPositions.removeAtIndex(0);
    mPositions.add(obj().location().pos().getXY());
    calcJoint();
}

void StateMain::procFixPos() {
    if (obj().mapColl().result().isDead()) {
        obj().dead();
    }
}

void StateMain::procObjCollReact() {}

void StateMain::calcJoint() {
    const Param& param = obj().param().waterBigWave();
    u32 interval = param._0;
    u32 jointNum = param._4;
    for (u32 i = 0; i < jointNum; i++) {
        Vector3 jointPos = mPositions[interval * (jointNum - 1 - i)].toVector3();
        Vector3 diff = jointPos - obj().location().pos();
        Vector3 trans;
        f32 z = diff.x * obj().target().getSign();
        trans.y = diff.y;
        trans.z = z + static_cast<f32>(i + 1);
        Matrix34 mtx = Matrix34::CreateTrans(trans);
        NodeLocalMtxAccessor localMtx = obj().model().model().nodes().at(targetNodes[i]).localMtx();
        localMtx.setRTMtx(mtx);
    }
}

}}}}  // namespace scn::step::weapon::waterbigwave
