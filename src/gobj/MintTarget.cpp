#include "gobj/MintTarget.h"

#include "gobj/Target.h"
#include "hel/common/PointerWrapper.h"
#include "hel/mint/AddOnMathDirection3.h"

namespace gobj {

namespace {

hel::common::PointerWrapper<Target> t_obj;

}

namespace MintTarget {

void Register(Target& obj) {
    t_obj.set(obj);
}

void Unregister(Target&) {
    t_obj.reset();
}

bool IsRightDir() {
    return t_obj->isRightDir();
}

void SetIsRightDir(bool isRightDir) {
    t_obj->setIsRightDir(isRightDir);
}

f32 GetSign() {
    return t_obj->getSign();
}

void Invert() {
    t_obj->invert();
}

void LoadDirection3() {
    hel::mint::AddOnMathDirection3::Set(t_obj->getDirection3());
}

}
}
