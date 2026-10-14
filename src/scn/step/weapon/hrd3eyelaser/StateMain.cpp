#include "scn/step/weapon/hrd3eyelaser/StateMain.h"

#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/GearModel.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/hrd3eyelaser/Custom.h"

using hel::common::DynamicCastToRef;
using hel::math::Matrix34;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace weapon {
namespace hrd3eyelaser {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), mBoss(), mLength(0.0f), _1C(0.0f), mIsHit(false) {
    obj().mapColl().setValid(false);
    obj().model().rotCtrl().setValid(false);
    obj().model().reqScript(0);
    obj().model().setScale(Vector3::ALL_ONE * 0.1f);
}

StateMain::~StateMain() {
    obj().effect().normal().release();
}

void StateMain::procAnim() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    f32 scale = obj().model().getTotalScale().x;
    f32 max = custom.getLengthMax() / scale;
    mLength += 30.0f;
    if (mLength > max) {
        mLength = max;
        if (!mIsHit) {
            mIsHit = true;
            obj().effect().normal().requestN(static_cast<effect::Kind>(0x2EE), 2, 1.0f / obj().model().getTotalScale().x);
        }
    }
    obj().model().model().nodes().at(2).localMtx().setRTMtx(
        Matrix34::CreateTrans(Vector3(0.0f, 0.0f, mLength))
    );
}

void StateMain::procMove() {}

void StateMain::procFixPos() {}

}}}}  // namespace scn::step::weapon::hrd3eyelaser
