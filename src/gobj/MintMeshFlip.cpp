#include "gobj/MintMeshFlip.h"

#include "gobj/MeshFlip.h"
#include "hel/common/PointerWrapper.h"

namespace gobj {

namespace {

hel::common::PointerWrapper<MeshFlip> t_obj;

}

namespace MintMeshFlip {

void Register(MeshFlip& obj) {
    t_obj.set(obj);
}

void Unregister(MeshFlip&) {
    t_obj.reset();
}

void Flip(u32 index) {
    t_obj->flip(index);
}

}}  // namespace gobj::MintMeshFlip
