#include "scn/step/enemy/cappyhat/Custom.h"

#include "hel/math/Vector2.h"
#include "mcoll/LandManager.h"
#include "scn/step/Component.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/Culling.h"
#include "scn/step/chara/Location.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/map/LandManager.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;
using hel::geo::Rect;
using hel::math::Vector2;

namespace scn {
namespace step {
namespace enemy {
namespace cappyhat {

Custom::Custom(Enemy& enemy) : CustomBase(enemy) {}

bool Custom::onInit() {
    obj().culling().setValid(false);
    return false;
}

void Custom::onProcFixPos() {
    if (chkCulling()) {
        obj().dead();
    }
}

bool Custom::chkCulling() {
    Vector2 pos = obj().location().pos().getXY();
    if (pos.x < 0.0f || obj().comp().mapLandManager().native().gridWidth() < pos.x) {
        return true;
    }
    Rect rect = calcCullingRect();
    return !rect.isInclude(pos.x, pos.y);
}

Rect Custom::calcCullingRect() {
    Rect base(14.0f, -10.0f, -8.0f * obj().comp().mainCamera().getAspect() - 2.0f,
              8.0f * obj().comp().mainCamera().getAspect() + 2.0f);
    Rect rect(base);
    rect.trans(obj().comp().mainCamera().getCenterCulling().x, obj().comp().mainCamera().getCenterCulling().y);
    Rect current(base);
    current.trans(obj().comp().mainCamera().getCenter().x, obj().comp().mainCamera().getCenter().y);
    rect.margeUnion(current);
    f32 margin = 0.5f * obj().comp().cameraController().getCullingMarginHeight();
    f32 aspect = obj().comp().mainCamera().getAspect();
    rect._0 += margin;
    rect._4 -= margin;
    rect._8 -= aspect;
    rect._C += aspect;
    return rect;
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

}}}}  // namespace scn::step::enemy::cappyhat
