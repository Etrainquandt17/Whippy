#include "scn/step/weapon/mahoroaicicle/StateMain.h"

#include "app/Random.h"
#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/GearModel.h"
#include "gobj/NodeRepos.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/mahoroaicicle/StateFall.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace weapon {
namespace mahoroaicicle {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), mFrame(0), mStartPos(weapon->location().pos()), mRot(0.0f) {
    obj().model().rotCtrl().setValid(false);
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x207));
    obj().objColl().addAttack(0, 1.0f, hel::math::Vector2(0.0f, 4.0f), hel::math::Vector2(0.0f, 1.0f));
    obj().objColl().setAttackCenter(0, hel::math::Vector2::ZERO);
    mRot = app::Random::RandF(0.0f, 360.0f);
    obj().model().model().nodes().at(0).localMtx().setRTMtx(hel::math::Matrix34::CreateRotXYZDeg(hel::math::Vector3(0.0f, mRot, 0.0f)));
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x40E), 0);
}

StateMain::~StateMain() {}

void StateMain::procAnim() {
    if (mFrame < 30) {
        mFrame++;
    } else {
        obj().stateChanger().setNextState<StateFall, Weapon*, f32>(objPtr(), mRot);
    }
}

void StateMain::procMove() {
    f32 t = static_cast<f32>(mFrame) / 30.0f;
    hel::math::Vector3 pos = mStartPos;
    pos.y -= 2.0f * hel::math::Math::SinDegF(90.0f * t);
    obj().location().setPos(pos);
}

void StateMain::procFixPos() {}

}}}}  // namespace scn::step::weapon::mahoroaicicle
