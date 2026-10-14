#include "gobj/MintModel.h"

#include "g3d/MintNodeAccessor.h"
#include "gobj/Model.h"
#include "gobj/NodeRepos.h"
#include "hel/common/PointerWrapper.h"

using hel::common::PointerWrapper;
using hel::math::Vector3;

namespace gobj {

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

void LoadNode(u32 index) {
    g3d::MintNodeAccessor::RegisterForce(t_obj->nodes().at(index));
}

void SetScale(f32 x, f32 y, f32 z) {
    t_obj->setScale(Vector3(x, y, z));
}

}}  // namespace gobj::MintModel
