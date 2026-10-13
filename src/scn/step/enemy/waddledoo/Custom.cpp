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

namespace scn {
namespace step {
namespace enemy {
namespace waddledoo {

Custom::Custom(Enemy& enemy) : CustomBase(enemy) {}

void Custom::setupSuperEnemyEffect() {
    hel::math::Vector3 center = obj().location().toCenter();
    obj().effect().super().requestN(effect::KIND_132, 0, center);
    obj().effect().super().requestN(effect::KIND_37, 10);
    f32 scale = 1.0f / Utility::GetModelScaleBySizeType(obj());
    g3d::NodeAccessor node = obj().model().model().nodes().at(2);
    node.localMtx().setScale(hel::math::Vector3(scale, scale, scale));
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

}}}}  // namespace scn::step::enemy::waddledoo
