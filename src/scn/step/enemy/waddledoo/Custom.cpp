#include "scn/step/enemy/waddledoo/Custom.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/GearModel.h"
#include "mintglue/VectorInline.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Utility.h"

using g3d::NodeAccessor;
using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace waddledoo {

Custom::Custom(Enemy& enemy) : CustomBase(enemy) {}

void Custom::setupSuperEnemyEffect() {
    Vector3 center = obj().location().toCenter();
    obj().effect().super().requestN(effect::KIND_132, 0, center);
    obj().effect().super().requestN(effect::KIND_37, 10);
    f32 scale = 1.0f / Utility::GetModelScaleBySizeType(obj());
    NodeAccessor node = obj().model().model().nodes().at(2);
    node.localMtx().setScale(Vector3(scale, scale, scale));
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

}}}}  // namespace scn::step::enemy::waddledoo
