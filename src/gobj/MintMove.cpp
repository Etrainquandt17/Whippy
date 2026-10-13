#include "gobj/MintMove.h"

#include "gobj/Move.h"
#include "hel/common/PointerWrapper.h"

namespace gobj {

namespace {

hel::common::PointerWrapper<Move> t_obj;

}

namespace MintMove {

void Register(Move& obj) {
    t_obj.set(obj);
}

void Unregister(Move&) {
    t_obj.reset();
}

f32 GetSpeedH() {
    return t_obj->velocity().x;
}

f32 GetSpeedV() {
    return t_obj->velocity().y;
}

f32 GetSpeedD() {
    return t_obj->velocity().z;
}

void SetSpeedH(f32 speed) {
    t_obj->setSpeedH(speed);
}

void SetSpeedV(f32 speed) {
    t_obj->setSpeedV(speed);
}

void SetSpeedD(f32 speed) {
    t_obj->setSpeedD(speed);
}

}
}
