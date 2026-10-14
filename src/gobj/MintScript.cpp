#include "gobj/MintScript.h"

#include "gobj/Script.h"
#include "hel/common/PointerWrapper.h"

using hel::common::PointerWrapper;

namespace gobj {

namespace {

PointerWrapper<Script> t_obj;

}

namespace MintScript {

void Register(Script& obj) {
    t_obj.set(obj);
}

void Unregister(Script&) {
    t_obj.reset();
}

u32 PrevScriptIndex() {
    return t_obj->prevScriptIndex();
}

}}  // namespace gobj::MintScript
