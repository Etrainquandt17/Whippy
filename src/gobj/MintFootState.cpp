#include "gobj/MintFootState.h"

#include "gobj/FootState.h"
#include "hel/common/PointerWrapper.h"

namespace gobj {

namespace {

hel::common::PointerWrapper<FootState> t_obj;

}

namespace MintFootState {

void Register(FootState& obj) {
    t_obj.set(obj);
}

void Unregister(FootState&) {
    t_obj.reset();
}

bool IsGround() {
    return t_obj->isGround();
}

bool IsAir() {
    return t_obj->isAir();
}

}}  // namespace gobj::MintFootState
