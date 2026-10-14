#include "scn/step/chara/MintModel.h"

#include "hel/common/PointerWrapper.h"
#include "mintglue/VectorInline.h"
#include "scn/step/chara/Model.h"

using hel::common::PointerWrapper;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace chara {

namespace {

PointerWrapper<Model> t_obj;

}

namespace MintModel {

void Register(Model& obj) {
    t_obj.set(obj);
}

void Unregister(Model&) {
    t_obj.reset();
}

void SetScale3(f32 x, f32 y, f32 z) {
    t_obj->setScale(Vector3(x, y, z));
}

}}}}  // namespace scn::step::chara::MintModel
