#include "scn/step/weapon/goliathenergyball/StateMain.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "scn/step/Component.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/chara/Culling.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/goliathenergyball/Custom.h"
#include "scn/step/weapon/goliathenergyball/Param.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace weapon {
namespace goliathenergyball {

namespace {

struct ScaleRateDesc {
    f32 mRate;
    f32 mValue;
};

const ScaleRateDesc T_SCALE_RATE_DESC[] = {
    { 0.0f, 0.0f }, { 0.3f, 0.0f }, { 0.5f, 0.5f }, { 0.7f, 0.5f }, { 0.9f, 1.0f }, { 2.0f, 1.0f },
};

}

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), mStartPos(obj().location().pos()), mFrame(0) {
    obj().mapColl().setValid(false);
    obj().culling().setValid(false);
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x1F3));
    obj().effect().normal().changeLayer(static_cast<core::DrawLayerKind>(8));
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x296), 0);
    obj().soundSE().start(0x364);
    obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(5));
}

StateMain::~StateMain() {}

void StateMain::procAnim() {
    const Param& param = obj().param().goliathEnergyBall();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (mFrame < custom.getScaleUpFrame()) {
        mFrame++;
    }
    f32 rate = static_cast<f32>(mFrame) / static_cast<f32>(custom.getScaleUpFrame());
    f32 scale = 1.0f;
    for (u32 i = 1; i < 6; i++) {
        if (rate < T_SCALE_RATE_DESC[i].mRate) {
            const ScaleRateDesc& prev = T_SCALE_RATE_DESC[i - 1];
            const ScaleRateDesc& next = T_SCALE_RATE_DESC[i];
            f32 t = (rate - prev.mRate) / (next.mRate - prev.mRate);
            scale = hel::math::Math::LinearInterpolation(
                1.0f, param._0, hel::math::Math::LinearInterpolation(prev.mValue, next.mValue, t)
            );
            break;
        }
    }
    obj().model().setScale(hel::math::Vector3::ALL_ONE * scale);
    if (mFrame == static_cast<u32>(T_SCALE_RATE_DESC[1].mRate * static_cast<f32>(custom.getScaleUpFrame()))
        || mFrame == static_cast<u32>(T_SCALE_RATE_DESC[3].mRate * static_cast<f32>(custom.getScaleUpFrame()))) {
        obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(5));
    }
    if (mFrame < custom.getScaleUpFrame()) {
        obj().objColl().clearAttack();
        obj().objColl().addAttack(0, param._8 * (scale / param._0));
    }
}

void StateMain::procMove() {
    const Param& param = obj().param().goliathEnergyBall();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (mFrame < custom.getScaleUpFrame()) {
        f32 rate = static_cast<f32>(mFrame) / static_cast<f32>(custom.getScaleUpFrame());
        f32 offset = 0.0f;
        for (u32 i = 1; i < 6; i++) {
            if (rate < T_SCALE_RATE_DESC[i].mRate) {
                const ScaleRateDesc& prev = T_SCALE_RATE_DESC[i - 1];
                const ScaleRateDesc& next = T_SCALE_RATE_DESC[i];
                f32 t = (rate - prev.mRate) / (next.mRate - prev.mRate);
                offset = hel::math::Math::LinearInterpolation(
                    0.0f, param._0, hel::math::Math::LinearInterpolation(prev.mValue, next.mValue, t)
                );
                break;
            }
        }
        hel::math::Vector3 pos = mStartPos;
        pos.y += offset;
        obj().location().setPos(pos);
    }
}

void StateMain::procFixPos() {}

}}}}  // namespace scn::step::weapon::goliathenergyball
