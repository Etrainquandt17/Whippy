#include "scn/step/enemy/elec/Custom.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/GearModel.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/Utility.h"

using g3d::NodeAccessor;
using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;
using hel::math::Math;
using hel::math::Matrix34;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace elec {

Custom::Custom(Enemy& enemy) : CustomBase(enemy) {
    obj().nururi().changeSetting(static_cast<nururi::Mode>(1));
}

void Custom::onProcFixPos() {
    Vector3 dir = Utility::GetNearestPlayerPos(obj()).toVector3() - obj().location().pos();
    f32 angle = Math::Atan2DegF(dir.y, dir.x);
    NodeAccessor node = obj().model().model().nodes().at(2);
    Matrix34 mtx = Matrix34::CreateRotXYZDeg(Vector3(0.0f, angle, 0.0f));
    node.localMtx().setRTMtx(mtx);
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

}}}}  // namespace scn::step::enemy::elec
